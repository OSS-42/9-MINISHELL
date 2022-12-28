/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 21:05:24 by ewurstei          #+#    #+#             */
/*   Updated: 2022/12/28 09:34:45 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_next_char(t_vault *data, int row, int i)
{
	if (data->rl_dec[row][i + 1] == '\''
		|| data->rl_dec[row][i + 1] == '\"')
	{
		i = i - 2;
		while (data->rl_dec[row][i])
		{
			if (data->rl_dec[row][i] != '\''
				|| data->rl_dec[row][i] != '\"'
					|| data->rl_dec[row][i] != '$')
				i++;
			data->buffer[data->pos] = data->rl_dec[row][i];
			data->pos++;
			i++;
		}
	}
	return (i);
}

void	parse_row(t_vault *data, int row)
{
	int		i;

	i = 0;
	data->pos = 0;
	while (data->rl_dec[row] && data->rl_dec[row][i])
	{
		data->dollar_var_len = 0;
		if (ft_isinset(data->rl_dec[row][i]) == 0)
			data->buffer[data->pos] = data->rl_dec[row][i];
		else if (ft_isinset(data->rl_dec[row][i]) == 1)
			i = sgle_quote_mngmt(data, row, i);
		else if (ft_isinset(data->rl_dec[row][i]) == 2)
			i = dble_quote_mngmt(data, row, i);
		else if (ft_isinset(data->rl_dec[row][i]) == 3)
		{
			dollar_var_to_extract(data, row, i);
			i = i + data->dollar_var_len;
			data->pos--;
		}
		i++;
		data->pos++;
	}
	free (data->rl_dec[row]);
	data->rl_dec[row] = ft_calloc(sizeof(char), ft_strlen(data->buffer) + 1);
	ft_strlcpy(data->rl_dec[row], data->buffer, 500);
}

int	sgle_quote_mngmt(t_vault *data, int row, int i)
{
	i++;
	while (data->rl_dec[row][i] && data->rl_dec[row][i] != '\'')
	{
		data->buffer[data->pos] = data->rl_dec[row][i];
		data->pos++;
		i++;
	}
	data->pos = data->pos - 1;
	return (i);
}

int	dble_quote_mngmt(t_vault *data, int row, int i)
{
	i++;
	while (data->rl_dec[row][i] && data->rl_dec[row][i] != '\"')
	{
		if (data->rl_dec[row][i] == '$'
			&& ft_char_env_var(data->rl_dec[row][i + 1]) == 1)
		{
			dollar_var_to_extract(data, row, i);
			i = i + data->dollar_var_len;
			data->pos--;
		}
		else
			data->buffer[data->pos] = data->rl_dec[row][i];
		data->pos++;
		i++;
	}
	data->pos--;
	return (i);
}

void	row_parsing(t_vault *data)
{
	int	row;

	row = 0;
	data->b_in->forget_minus = 0;
	data->b_in->minus_n = 0;
	data->b_in->dont_do_minus = 0;
	while (data->rl_dec[row] && data->rl_dec[row][0])
	{
		data->buffer = ft_calloc(sizeof(char), 500);
		parse_row(data, row);
		free(data->buffer);
		data->b_in->forget_minus = 0;
		// data->b_in->echo_first = 0;
		row++;
	}
}
