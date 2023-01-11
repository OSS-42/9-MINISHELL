/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 21:05:24 by ewurstei          #+#    #+#             */
/*   Updated: 2023/01/11 13:48:52 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	final_quotes_removing(t_vault *data, int line)
{
	int	row;
	int	size;

	row = 0;
	data->pos = 0;
	data->buffer = ft_calloc(sizeof(char), 500);
	size = line_count(data, line);
	data->cmd->opt = ft_calloc(sizeof(char *), size + 2);
	row = quote_parsing_removal(data, line);
	ft_free_n_null (data->cmd->opt[row]);
	data->cmd->opt[row] = ft_strdup(data->buffer);
	ft_free_n_null (data->buffer);
	data->buffer = NULL;
}

int	quote_parsing_removal(t_vault *data, int line)
{
	int	i;
	int	row;

	i = -1;
	row = 0;
	while (data->tab_arg[line] && data->tab_arg[line][++i])
	{
		if (data->tab_arg[line][i] == ' ')
		{
			data->cmd->opt[row] = ft_strdup(data->buffer);
			ft_free_n_null (data->buffer);
			data->buffer = ft_calloc(sizeof(char), 500);
			row++;
			data->pos = -1;
		}
		else if (ft_isinset(data->tab_arg[line][i]) == 0
			|| ft_isinset(data->tab_arg[line][i]) == 3)
			data->buffer[data->pos] = data->tab_arg[line][i];
		else if (ft_isinset(data->tab_arg[line][i]) == 1)
			i = quote_mngmt(data, line, i, data->tab_arg[line][i]);
		else if (ft_isinset(data->tab_arg[line][i]) == 2)
			i = quote_mngmt(data, line, i, data->tab_arg[line][i]);
		data->pos++;
	}
	return (row);
}

int	line_count(t_vault *data, int line)
{
	int	line_count;
	int	i;

	i = 0;
	line_count = 0;
	while (data->tab_arg[line] && data->tab_arg[line][i])
	{
		if (data->tab_arg[line][i] == '\'' || data->tab_arg[line][i] == '\"')
		{
			data->quote->quote_priority = data->tab_arg[line][i];
			while (data->tab_arg[line][i] != data->quote->quote_priority)
				i++;
		}
		else if (data->tab_arg[line][i] == ' ')
			line_count++;
		i++;
	}
	return (line_count);
}

int	quote_mngmt(t_vault *data, int line, int i, char quote)
{
	i++;
	while (data->tab_arg[line][i] && data->tab_arg[line][i] != quote)
	{
		data->buffer[data->pos] = data->tab_arg[line][i];
		data->pos++;
		i++;
	}
	data->pos = data->pos - 1;
	return (i);
}

int	check_is_redir(t_vault *data, int row, int i)
{
	int	end;

	end = 0;
	if (i != 0)
	{
		i--;
		while (data->rl_dec[row][i] == ' ')
			i--;
		if (data->rl_dec[row][i] == '<' || data->rl_dec[row][i] == '>')
			return (TRUE);
	}
	else if (row != 0)
	{
		end = ft_strlen(data->rl_dec[row - 1]) - 1;
		if (data->rl_dec[row - 1][end] == '<'
			|| data->rl_dec[row - 1][end] == '>')
			return (TRUE);
	}
	return (FALSE);
}
