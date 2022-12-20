/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   explore_readline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbertin <mbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:55:29 by momo              #+#    #+#             */
/*   Updated: 2022/12/20 14:39:13 by mbertin          ###   ########.fr       */
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
		row_parsing(data);
		parse_minus(data);
		create_tab_arg(data);
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

void	create_tab_arg(t_vault *data)
{
	int		row;
	int		line;
	size_t	i;
	char	*temp;

	row = 0;
	temp = NULL;
	// printf("pipe count : %d\n", data->flag->pipe_count);
	data->tab_arg = ft_calloc(sizeof(char *), (data->flag->pipe_count + 1) + 1);
	i = 0;
	while (data->rl_decomp[row][i] && data->rl_decomp[row][i] != '|')
		i++;
	if (i == ft_strlen(data->rl_decomp[row]))
	{
		// printf("%zu\n", i);
		// printf("%zu\n", ft_strlen(data->rl_decomp[row]));
		line = 0;
		while (data->rl_decomp[row] && data->rl_decomp[row][0])
		{
			if (data->rl_decomp[row][0] == '|')
			{
				line ++;
				row++;
			}
			if (data->tab_arg[line] == NULL)
			{
				data->tab_arg[line] = ft_strdup(data->rl_decomp[row]);
				if (data->rl_decomp[row + 1] && data->rl_decomp[row + 1][0] && data->rl_decomp[row + 1][0] != '|')
					data->tab_arg[line] = ft_strjoin(data->tab_arg[line], " ");
			}
			else
			{
				temp = ft_strjoin(data->tab_arg[line], data->rl_decomp[row]);
				free (data->tab_arg[line]);
				data->tab_arg[line] = ft_strdup(temp);
				free (temp);
				if (data->rl_decomp[row + 1] && data->rl_decomp[row + 1][0] && data->rl_decomp[row + 1][0] != '|')
					data->tab_arg[line] = ft_strjoin(data->tab_arg[line], " ");
			}
			row++;
		}
		line++;
		data->tab_arg[line] = NULL;
	// else
	// {
	// 	remove_pipe_form_str();
	// }
		// print_double_array(data->tab_arg);
	}
}
