/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_analyzis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbertin <mbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 10:05:10 by mbertin           #+#    #+#             */
/*   Updated: 2023/01/11 19:00:26 by mbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	rl_prio_n_qty(t_vault *data, int i, char c)
{
	while (data->read_line[i])
	{
		if (data->read_line[i] == '\"' || data->read_line[i] == '\'')
		{
			c = data->read_line[i];
			if (c == '\"')
				data->quote->double_quote_count++;
			else if (c == '\'')
				data->quote->simple_quote_count++;
			i = move_index_delimiter(data, i, c);
			if (!data->read_line[i])
			{
				// error_message(data, "missing or wrong arguments", "1\0"); Maintenant dans explore_readline
				return (FALSE);
			}
			else if (c == '\"')
				data->quote->double_quote_count++;
			else if (c == '\'')
				data->quote->simple_quote_count++;
		}
		i++;
	}
	return (TRUE);
}

void	flag_count(t_vault *data, int i, int j)
{
	char	c;

	c = '\0';
	while (data->rl_dec[i] && data->rl_dec[i][0])
	{
		while (data->rl_dec[i][j])
		{
			if (data->rl_dec[i][j] == '\'' || data->rl_dec[i][j] == '\"')
			{
				c = data->rl_dec[i][j];
				j++;
				while (data->rl_dec[i][j] != c)
					j++;
			}
			if (data->rl_dec[i][j] == '|')
				data->flag->pipe_count++;
			j++;
		}
		j = 0;
		i++;
	}
}

int	pipe_check(t_vault *data)
{
	int	i;

	i = -1;
	while (data->read_line[++i])
	{
		if (data->read_line[i] == '\'' || data->read_line[i] == '\"')
		{
			data->quote->quote_priority = data->read_line[i];
			i = move_index_delimiter(data, i, data->quote->quote_priority);
		}
		else if (data->read_line[i] == '|')
		{
			if (check_pipe_syntax(data, i) == 1)
			{
				error_message(data, "missing or wrong arguments", "1\0");
				return (1);
			}
			else
				return (0);
		}
	}
	return (0);
}

int	move_index_delimiter(t_vault *data, int i, char delimiter)
{
	i++;
	while (data->read_line[i] && data->read_line[i] != delimiter)
		i++;
	return (i);
}

int	check_pipe_syntax(t_vault *data, int i)
{
	while (data->read_line[++i])
	{
		if (data->read_line[i] != ' ' && data->read_line[i] != '|')
		{
			g_error_code = 0;
			return (0);
		}
		else if (data->read_line[i] == '|' && g_error_code == 1)
			return (1);
		g_error_code = 1;
	}
	return (1);
}
