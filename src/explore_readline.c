/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   explore_readline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:55:29 by momo              #+#    #+#             */
/*   Updated: 2022/12/31 00:05:39 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	explore_readline(t_vault *data)
{
	data->rl_dec = ft_split(data->read_line, ' ');
	if (rl_prio_n_qty(data, 0, '\0') == TRUE)   // se fait sur readline
	{
		find_str_quote(data);					// se fait sur readline
		flag_count(data, 0, 0);					// se fait sur rl_dec
		dollar_parsing(data);					// se fait sur rl_dec
		detached_quote_tab(data);				// se fait sur rl_dec
		check_for_pipe(data);					// se fait sur rl_dec
//		row_parsing(data);						//
		create_tab_arg(data, -1, 0);
		piping(data);
		reset_io(data);
		if (data->flag->fd != 0)
			close (data->flag->fd);
	}
	return ;
}

void	dollar_parsing(t_vault *data)
{
	int	i;
	int	row;

	i = 0;
	row = 0;
	data->pos = 0;
	data->buffer = ft_calloc(sizeof(char), 500);
	while (data->rl_dec[row] && data->rl_dec[row][i])
	{
		data->dollar_var_len = 0;
		if (ft_isinset(data->rl_dec[row][i]) == 0)
			data->buffer[data->pos] = data->rl_dec[row][i];
		else if (ft_isinset(data->rl_dec[row][i]) == 1)
		{
			data->quote->quote_priority = data->rl_dec[row][i];
			while (data->rl_dec[row][i] != data->quote->quote_priority)
				i++;
		}
		else if (ft_isinset(data->rl_dec[row][i]) == 2)
		{
			data->quote->quote_priority = data->rl_dec[row][i];
			while (data->rl_dec[row][i] != data->quote->quote_priority)
			{
				if (data->rl_dec[row][i] == '$'
				&& ft_char_env_var(data->rl_dec[row][i + 1]) == 1)
				{
					dollar_var_to_expand(data, row, i);
					i = i + data->dollar_var_len;
					data->pos--;
				}
				else
					data->buffer[data->pos] = data->rl_dec[row][i];
				data->pos++;
				i++;
			}
		}
		else if (ft_isinset(data->rl_dec[row][i]) == 3)
		{
			i = i + data->dollar_var_len;
			data->pos--;
			dollar_var_to_expand(data, row, i);
		}
		i++;
		data->pos++;
	}
	free (data->rl_dec[row]);
	data->rl_dec[row] = ft_calloc(sizeof(char), ft_strlen(data->buffer) + 1);
	ft_strlcpy(data->rl_dec[row], data->buffer, 500);
	free (data->buffer);
}

void	piping(t_vault *data)
{
	int	i;

	i = 0;
	data->flag->pipe = ft_calloc(sizeof(int *), (data->flag->pipe_count) + 1);
	while (i < data->flag->pipe_count)
	{
		data->flag->pipe[i] = ft_calloc(sizeof(int), 2);
		if (pipe(data->flag->pipe[i]) == -1)
		{
			g_error_code = 8;
			error_message(data);
		}
		i++;
	}
	launching_exec(data);
	i = 0;
	close_pipe(data);
	while (i < data->flag->pipe_count + 1)
	{
		data->child_id = waitpid(data->pid[i], &data->status, 0);
		i++;
	}
}

void	launching_exec(t_vault *data)
{
	int		line;

	line = -1;
	data->pid = ft_calloc(sizeof(int), data->flag->pipe_count + 1);
	while (data->tab_arg[++line] && data->tab_arg[line][0])
	{
		if (data->flag->pipe_count == 0)
		{
			execute_redirection(data, line, 0);
			if (data->tab_arg[line][0] != '\0')
			{
				//data->cmd->opt = ft_split(data->tab_arg[line], ' ');
				// split intelligent ici (final_quotes_removing(line))
				final_quotes_removing(data, line);
				data->cmd->name = ft_strdup(data->cmd->opt[0]);
				recompose_tab_arg(data, line);
				if (is_special_built_in(data, line) == TRUE)
					built_in(data, line);
				else
					forking(data, line, 1);
			}
		}
		else
			forking(data, line, 2);
	}
	free(data->pid);
}

void	forking(t_vault *data, int line, int type)
{
	if (type == 1)
	{
		child_creation(data, line);
		if (data->pid[line] == 0)
		{
			find_prog(data, line);
			ft_exit(data);
		}
	}
	else if (type == 2)
	{
		child_creation(data, line);
		if (data->pid[line] == 0)
		{
			dup_fds(data, line);
			execute_redirection(data, line, 0);
			if (data->tab_arg[line][0] != '\0')
				in_child_exec(data, line);
		}
	}
}

void	child_creation(t_vault *data, int line)
{
	data->pid[line] = fork();
	if (data->pid[line] == -1)
	{
		g_error_code = 9;
		error_message(data);
		ft_exit(data);
	}
}

//en erreur 28/12
// Quand on rentre un mauvais input avec < on sort de minishell si il y une
// seul commande avec echo
// Creer un flag qui empeche lexecution de commande si mauvais input
// Continuer de tester echo test 12 > "tes>t"

//possibilite de suivre le child :
//1. ouvrir un 2e terminal
//2. lancer lldb
// lire  : https://lldb.llvm.org/use/map.html
//3a. pro at -n minishell -w
//ou 3b. pro at -p #pid
