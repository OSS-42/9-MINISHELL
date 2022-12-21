/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   explore_readline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:55:29 by momo              #+#    #+#             */
/*   Updated: 2022/12/21 14:06:58 by ewurstei         ###   ########.fr       */
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
		row_parsing(data);
		parse_minus(data); //echo doit appeler ce parsing
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

	data->tab_arg = ft_calloc(sizeof(char *), (data->flag->pipe_count + 1) + 1);
	while (data->rl_decomp[++row] && data->rl_decomp[row][0])
	{
		if (data->rl_decomp[row][0] == '|')
		{
			if (data->rl_decomp[row][1] == '\0')
			{
				line++;
				row++;
			}
			else if (data->rl_decomp[row][1] == '|')
				return ;
		}
		i = check_if_pipe(data, row, i);
		if (i == ft_strlen(data->rl_decomp[row]))
			switch_lines(data, row, line);
		else if (ft_strlen(data->rl_decomp[row]) > 1)
			row = remove_pipe_from_str(data, row, &line) - 1;
	}
	line++;
	data->tab_arg[line] = NULL;
}

int	remove_pipe_from_str(t_vault *data, int row, int *line)
{
	int		i;
	int		count;
	char	*temp;
	char	*buf;

	i = 0;
	count = 0;
	buf = NULL;
	while (data->rl_decomp[row] && data->rl_decomp[row][i])
	{
		temp = check_if_pipe2(data, row, &i, &count);
		switch_lines2(data, row, *line, temp);
		if (count > 0)
		{
			(*line)++;
			count--;
		}
		temp = copy_in_temp(data, row, &i, 0);
		if (data->rl_decomp[row][i] || temp)
			switch_lines2(data, row, *line, temp);
		i = 0;
		row ++;
	}
	return (row);
}
