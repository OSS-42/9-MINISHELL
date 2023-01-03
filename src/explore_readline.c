/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   explore_readline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:55:29 by momo              #+#    #+#             */
/*   Updated: 2023/01/02 23:31:07 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	explore_readline(t_vault *data)
{
	data->rl_dec = ft_split(data->read_line, ' ');
	if (rl_prio_n_qty(data, 0, '\0') == TRUE)
	{
		find_str_quote(data);					// se fait sur readline
		check_for_pipe(data);					// se fait sur rl_dec
		if (pipe_check(data) == 1)
			return ;						// se fait sur readline
		flag_count(data, 0, 0);					// se fait sur rl_dec
		dollar_parsing(data);					// se fait sur rl_dec
		create_tab_arg(data, -1, 0);
		// execute_redirection(data, 0, 0);
		if (!(data->tab_arg[0]))
		{
			error_message(data, "putain con, regarde ce que tu ecris", "1\0");
			return ;
		}
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
	while (data->rl_dec[row])
	{
		data->buffer = ft_calloc(sizeof(char), 500);
		while (data->rl_dec[row][i])
		{
			data->dollar_var_len = 0;
			if (ft_isinset(data->rl_dec[row][i]) == 0)
				data->buffer[data->pos] = data->rl_dec[row][i];
			else if (ft_isinset(data->rl_dec[row][i]) == 1)
			{
				data->quote->quote_priority = data->rl_dec[row][i];
				data->buffer[data->pos] = data->rl_dec[row][i];
				i++;
				data->pos++;
				while (data->rl_dec[row][i] != data->quote->quote_priority)
				{
					data->buffer[data->pos] = data->rl_dec[row][i];
					data->pos++;
					i++;
				}
				data->buffer[data->pos] = data->rl_dec[row][i];
			}
			else if (ft_isinset(data->rl_dec[row][i]) == 2)
			{
				data->quote->quote_priority = data->rl_dec[row][i];
				data->buffer[data->pos] = data->rl_dec[row][i];
				i++;
				data->pos++;
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
				data->buffer[data->pos] = data->rl_dec[row][i];
			}
			else if (ft_isinset(data->rl_dec[row][i]) == 3)
			{
				dollar_var_to_expand(data, row, i);
				i = i + data->dollar_var_len;
				data->pos--;
			}
			data->pos++;
			i++;
		}
		free (data->rl_dec[row]);
		data->rl_dec[row] = ft_calloc(sizeof(char), ft_strlen(data->buffer) + 1);
		//ft_strlcpy(data->rl_dec[row], data->buffer, 500);
		data->rl_dec[row] = ft_strdup(data->buffer);
		free (data->buffer);
		data->pos = 0;
		i = 0;
		row++;
	}
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
			error_message(data, "pipe creation error", "1\0");
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
	free(data->pid);
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
			if (data->tab_arg[line][0] != '\0' && data->fail_redir == FALSE)
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
	if (data->flag->heredoc_delimiter == TRUE)
	{
		data->flag->heredoc_delimiter = FALSE;
		unlink("temp_heredoc");
	}
}

void	forking(t_vault *data, int line, int type)
{
	if (type == 1)
	{
		child_creation(data, line);
		if (data->pid[line] == 0)
		{
			find_prog(data, line);
			exit_process(data);
		}
	}
	else if (type == 2)
	{
		child_creation(data, line);
		if (data->pid[line] == 0)
		{
			dup_fds(data, line);
			execute_redirection(data, line, 0);
			if (data->tab_arg[line][0] != '\0' && data->fail_redir == FALSE)
				in_child_exec(data, line);
		}
	}
}

void	child_creation(t_vault *data, int line)
{
	data->pid[line] = fork();
	if (data->pid[line] == -1)
	{
		error_message(data, "pid creation error", "1\0");
		exit_process(data);
	}
	if (data->pid[line] == 0)
	{
		data->error_fd = open(".tmp_error", O_CREAT | O_WRONLY | O_TRUNC, 0644);
		ft_putstr_fd("0\0", data->error_fd);
	}
}

// À corriger :
// Gestion des fd DUO
// Gestion des leaks DUO
// Probleme multiple heredoc MORGAN
// Probleme de fd
// Probleme avec $? ERIC
// Mauvais comportement avec l'historique A DEBATTRE ERIC
// unset ERIC
// Export multiple variable dont une mauvaise au milieu ERIC
// cd écrit une erreur alors qu'il devrait pas MORGAN


//possibilite de suivre le child :
//1. ouvrir un 2e terminal
//2. lancer lldb
// lire  : https://lldb.llvm.org/use/map.html
//3a. pro at -n minishell -w
//ou 3b. pro at -p #pid
