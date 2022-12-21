/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 10:15:12 by ewurstei          #+#    #+#             */
/*   Updated: 2022/12/21 12:01:26 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	switch_lines(t_vault *data, int row, int line)
{
	char	*buffer;

	buffer = NULL;
	if (data->tab_arg[line] == NULL)
	{
		data->tab_arg[line] = ft_strdup(data->rl_decomp[row]);
		if (data->rl_decomp[row + 1] && data->rl_decomp[row + 1][0]
			&& data->rl_decomp[row + 1][0] != '|')
			data->tab_arg[line] = ft_strjoin(data->tab_arg[line], " ");
	}
	else
	{
		buffer = ft_strjoin(data->tab_arg[line], data->rl_decomp[row]);
		free (data->tab_arg[line]);
		data->tab_arg[line] = ft_strdup(buffer);
		free (buffer);
		if (data->rl_decomp[row + 1] && data->rl_decomp[row + 1][0]
			&& data->rl_decomp[row + 1][0] != '|')
			data->tab_arg[line] = ft_strjoin(data->tab_arg[line], " ");
	}
}

void	switch_lines2(t_vault *data, int row, int line, char *temp)
{
	char	*buffer;

	buffer = NULL;
	if (data->tab_arg[line] == NULL)
	{
		data->tab_arg[line] = ft_strdup(temp);
		if (data->rl_decomp[row + 1] && data->rl_decomp[row + 1][0]
			&& data->rl_decomp[row + 1][0] != '|')
			data->tab_arg[line] = ft_strjoin(data->tab_arg[line], " ");
	}
	else
	{
		buffer = ft_strjoin(data->tab_arg[line], temp);
		free (temp);
		free (data->tab_arg[line]);
		data->tab_arg[line] = ft_strdup(buffer);
		free (buffer);
		if (data->rl_decomp[row + 1] && data->rl_decomp[row + 1][0]
			&& data->rl_decomp[row + 1][0] != '|')
			data->tab_arg[line] = ft_strjoin(data->tab_arg[line], " ");
	}
}

size_t	check_if_pipe(t_vault *data, int row, int i)
{
	i = 0;
	if (data->rl_decomp[row][i] == '\'' || data->rl_decomp[row][i] == '\"')
	{
		data->quote->quote_priority = data->rl_decomp[row][i];
		i++;
		while (data->rl_decomp[row][i] != data->quote->quote_priority)
		i++;
	}
	while (data->rl_decomp[row][i] && data->rl_decomp[row][i] != '|')
		i++;
	return (i);
}
