/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_analyzis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbertin <mbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 10:05:10 by mbertin           #+#    #+#             */
/*   Updated: 2023/01/02 08:28:50 by mbertin          ###   ########.fr       */
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
			i++; // ++i sur le ligne suivante ?
			while (data->read_line[i] && data->read_line[i] != c)
				i++;
			if (!data->read_line[i])
			{
				ft_putstr_fd("1\0", data->error_fd);
				error_message(data, "missing or wrong arguments");
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
				// {
					// if (data->rl_dec[i][j] == '|')
					// 	if (data->rl_dec[i][j + 1] == c && data->rl_dec[i][j - 1] == c)
					// 		data->flag->pipe_count++;
					j++;
				// }
			}
			if (data->rl_dec[i][j] == '|')
				data->flag->pipe_count++;
			j++;
		}
		j = 0;
		i++;
	}
}

void	pipe_check(t_vault *data)
{
	int	i;

	i = 0;
	while (data->read_line[i])
	{
		if (data->read_line[i] == '\'' || data->read_line[i] == '\"')
		{
			data->quote->quote_priority = data->read_line[i];
			i++;
			while (data->read_line[i] != data->quote->quote_priority)
				i++;
		}
		else if (data->read_line[i] == '|')
		{
			i++;
			while (data->read_line[i])
			{
				if (data->read_line[i] != ' ' && data->read_line[i] != '|')
				{
					g_error_code = 0;
					return ;
				}
				else if (data->read_line[i] == '|' && g_error_code == 1)
				{
					ft_putstr_fd("1\0", data->error_fd);
					error_message(data, "missing or wrong arguments");
					ft_exit(data);
				}
				g_error_code = 1;
				i++;
			}
		}
		i++;
	}
}
