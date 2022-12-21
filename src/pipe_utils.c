/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 10:15:12 by ewurstei          #+#    #+#             */
/*   Updated: 2022/12/21 16:58:38 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"



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
			&& data->rl_decomp[row + 1][0] != '|'
			&& data->flag->pipe_count == 0)
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
			&& data->rl_decomp[row + 1][0] != '|'
			&& data->flag->pipe_count == 0)
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

char	*check_if_pipe2(t_vault *data, int row, int *i)
{
	char	*buffer;

	buffer = NULL;
	while (data->rl_decomp[row][*i] && data->rl_decomp[row][*i] != '|')
	{
		if ((data->flag->pipe_count > 0) && (data->rl_decomp[row][*i] == '\''
			|| data->rl_decomp[row][*i] == '\"'))
		{
			data->quote->quote_priority = data->rl_decomp[row][*i];
			(*i)++;
			buffer = copy_in_temp(data, row, i, data->quote->quote_priority);
		}
		else if (data->flag->pipe_count > 0)
		{
			if (buffer)
				buffer = ft_strjoin(buffer, copy_in_temp(data, row, i, '|'));
			else
			{
				buffer = copy_in_temp(data, row, i, '|');
				if (data->rl_decomp[row][*i] == '|')
					data->flag->pipe_count++;
			}
		}
		(*i)++;
	}
	return (buffer);
}

char	*copy_in_temp(t_vault *data, int row, int *i, char c)
{
	int		j;
	char	*buffer;

	j = 0;
	if (c == 0)
		c = '\0';
	buffer = ft_calloc(sizeof(char), 500);
	while (data->rl_decomp[row][*i] && data->rl_decomp[row][*i] != c)
	{
		buffer[j] = data->rl_decomp[row][*i];
		j++;
		(*i)++;
	}
	return (buffer);
}
