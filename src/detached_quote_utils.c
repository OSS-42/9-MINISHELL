/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detached_quote_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbertin <mbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 12:28:30 by mbertin           #+#    #+#             */
/*   Updated: 2022/12/29 09:45:38 by mbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	fill_out_quote(t_vault *data, int *i, int row, int *line)
{
	int	j;

	j = 0;
	data->temp[*i] = ft_calloc(sizeof(char),
			len_out_quote_dtch(data, row, *line) + 1);
	while (data->rl_dec[row][*line]
		&& data->rl_dec[row][*line] != '\''
		&& data->rl_dec[row][*line] != '\"')
	{
		data->temp[*i][j] = data->rl_dec[row][*line];
		j++;
		(*line)++;
	}
	(*i)++;
}

int	len_out_quote_dtch(t_vault *data, int row, int line)
{
	int	len;

	len = 0;
	while (data->rl_dec[row][line]
		&& data->rl_dec[row][line] != '\''
		&& data->rl_dec[row][line] != '\"')
	{
		line++;
		len++;
	}
	return (len);
}

void	fill_in_quote(t_vault *data, int *i, int row, int *line)
{
	int	j;

	j = 0;
	data->temp[*i] = ft_calloc(sizeof(char),
			len_in_quote_dtch(data, *line, row) + 1);
	data->quote->quote_priority
		= data->rl_dec[row][*line];
	data->temp[*i][j] = data->rl_dec[row][*line];
	(*line)++;
	j++;
	while (data->rl_dec[row][*line]
		!= data->quote->quote_priority)
	{
		data->temp[*i][j] = data->rl_dec[row][*line];
		j++;
		(*line)++;
	}
	data->temp[*i][j] = data->rl_dec[row][*line];
	(*line)++;
	(*i)++;
}

int	len_in_quote_dtch(t_vault *data, int line, int row)
{
	int	len;

	len = 1;
	data->quote->quote_priority = data->rl_dec[row][line];
	line++;
	while (data->rl_dec[row][line++] != data->quote->quote_priority)
		len++;
	len++;
	return (len);
}
