/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   explore_readline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:55:29 by momo              #+#    #+#             */
/*   Updated: 2022/12/21 23:12:59 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	row_parsing(t_vault *data)
{
	int	row;

	row = 0;
	data->b_in->forget_minus = 0;
	data->b_in->minus_n = 0;
	data->b_in->dont_do_minus = 0;
	while (data->rl_decomp[row] && data->rl_decomp[row][0])
	{
		data->buffer = ft_calloc(sizeof(char), 500);
		quote_priority(data, row);
		parse_row(data, row);
		free(data->buffer);
		data->b_in->forget_minus = 0;
		data->b_in->echo_first = 0;
		row++;
	}
}

void	explore_readline(t_vault *data)
{
	data->rl_decomp = ft_split(data->read_line, ' ');
	if (rl_prio_n_qty(data, 0, '\0') == TRUE)
	{
		find_str_quote(data);
		flag_count(data, 0, 0);
		execute_redirection(data, 0, 0);
		print_double_array(data->rl_decomp);
		create_tab_arg(data, -1, 0);
		print_double_array(data->tab_arg);
		row_parsing(data); //a realiser sur tab_arg et non rl_decomp
		built_in(data);
		dup2(data->flag->stdout_backup, STDOUT_FILENO);
		dup2(data->flag->stdin_backup, STDIN_FILENO);
	}
	return ;
}

void	built_in(t_vault *data)
{
	int	i;

	i = 1;
	if (ft_strcmp("cd", data->rl_decomp[0]) == 0)
		ft_cd(data, i);
	if (ft_strcmp("pwd", data->rl_decomp[0]) == 0)
		ft_pwd(data, i);
	if (ft_strcmp("echo", data->rl_decomp[0]) == 0)
		ft_echo(data, i);
	if (ft_strcmp("env", data->rl_decomp[0]) == 0)
		ft_env (data, 1);
	if (ft_strcmp("export", data->rl_decomp[0]) == 0)
		ft_export (data, i);
	if (ft_strcmp("unset", data->rl_decomp[0]) == 0)
		ft_unset (data, i);
	if (ft_strcmp("exit", data->rl_decomp[0]) == 0)
		ft_exit (data);
	return ;
}

void	create_tab_arg(t_vault *data, int row, int line)
{
	size_t	i;
	int		j;
	char	*buffer;

	data->tab_arg = ft_calloc(sizeof(char *), (data->flag->pipe_count + 1) + 1);
	buffer = NULL;
	while (data->rl_decomp[++row] && data->rl_decomp[row] && data->rl_decomp[row][0])
	{
		if (data->rl_decomp[row][0] == '|')
		{
			if (!(data->rl_decomp[row][1]))
			{
				line++;
				row++;
				if (!(data->rl_decomp[row]))
					return ; //retourner un code d'erreur.
			}
			else if (data->rl_decomp[row][1] == '|')
			{
				data->rl_decomp[row] = NULL;
				return ; //avant le return : vider la ligne.
			}
		}
		i = 0;
		j = 0;
		data->buffer = ft_calloc(sizeof(char), 500);
		while (data->rl_decomp[row] && data->rl_decomp[row][i])
		{
			if (data->rl_decomp[row][i] == '\'' || data->rl_decomp[row][i] == '\"')
			{
				data->quote->quote_priority = data->rl_decomp[row][i];
				while (data->rl_decomp[row][++i] != data->quote->quote_priority)
				{
					data->buffer[j] = data->rl_decomp[row][i];
					j++;
				}
			}
			else if (data->rl_decomp[row][i] == '|')
			{
				if (data->tab_arg[line] == NULL)
				{
					data->tab_arg[line] = ft_strdup(data->buffer);
					free (data->buffer);
					data->buffer = ft_calloc(sizeof(char), 500);
				}
				else
				{
					buffer = ft_strjoin(data->tab_arg[line], data->buffer);
					free (data->buffer);
					free (data->tab_arg[line]);
					data->tab_arg[line] = ft_strdup(buffer);
					free (buffer);
					data->buffer = ft_calloc(sizeof(char), 500);
				}
				line++;
				j = 0;
			}
			else
			{
				data->buffer[j] = data->rl_decomp[row][i];
				j++;
			}
			i++;
		}
		if (data->buffer[0] != '\0')
		{
			if (data->tab_arg[line] == NULL)
			{
				data->tab_arg[line] = ft_strdup(data->buffer);
				free (data->buffer);
				if (data->rl_decomp[row + 1] && data->rl_decomp[row + 1][0] && data->rl_decomp[row + 1][0] != '|')
					data->tab_arg[line] = ft_strjoin(data->tab_arg[line], " ");
			}
			else
			{
				buffer = ft_strjoin(data->tab_arg[line], data->buffer);
				free (data->buffer);
				free (data->tab_arg[line]);
				data->tab_arg[line] = ft_strdup(buffer);
				free (buffer);
				if (data->rl_decomp[row + 1] && data->rl_decomp[row + 1][0] && data->rl_decomp[row + 1][0] != '|')
					data->tab_arg[line] = ft_strjoin(data->tab_arg[line], " ");
			}
		}
	}
}
