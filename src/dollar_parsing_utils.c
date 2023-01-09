/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_parsing_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbertin <mbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:46:05 by ewurstei          #+#    #+#             */
/*   Updated: 2023/01/09 18:52:40 by mbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	dollar_parsing(t_vault *data)
{
	int	i;
	int	row;

	i = 0;
	row = 0;
	data->pos = 0;
	while (data->rl_dec[row])
	{
		data->buffer = ft_calloc(sizeof(char), 500);
		i = quote_parsing_with_dollar(data, row, i);
		free (data->rl_dec[row]);
		data->rl_dec[row] = ft_strdup(data->buffer);
		free (data->buffer);
		data->pos = 0;
		i = 0;
		row++;
	}
}

int	quote_parsing_with_dollar(t_vault *data, int row, int i)
{
	while (i < (int)ft_strlen(data->rl_dec[row]) && data->rl_dec[row][i])
	{
		data->dollar_var_len = 0;
		if (ft_isinset(data->rl_dec[row][i]) == 0)
			data->buffer[data->pos] = data->rl_dec[row][i];
		else if (ft_isinset(data->rl_dec[row][i]) == 1)
			i = sgl_quote_parsing(data, row, i);
		else if (ft_isinset(data->rl_dec[row][i]) == 2)
			i = dbl_quote_parsing(data, row, i);
		else if (ft_isinset(data->rl_dec[row][i]) == 3)
		{
			if (!(data->rl_dec[row][i + 1]))
				data->buffer[data->pos] = data->rl_dec[row][i];
			else
			{
				dollar_var_to_expand(data, row, i);
				i = i + data->dollar_var_len;
				data->pos--;
			}
		}
		data->pos++;
		i++;
	}
	return (i);
}

int	sgl_quote_parsing(t_vault *data, int row, int i)
{
	i = move_index(data, row, i);
	while (data->rl_dec[row][i] != data->quote->quote_priority)
	{
		data->buffer[data->pos] = data->rl_dec[row][i];
		data->pos++;
		i++;
	}
	data->buffer[data->pos] = data->rl_dec[row][i];
	return (i);
}

int	dbl_quote_parsing(t_vault *data, int row, int i)
{
	i = move_index(data, row, i);
	while (data->rl_dec[row][i] != data->quote->quote_priority)
	{
		if (data->rl_dec[row][i] == '$'
		&& ft_char_env_var(data->rl_dec[row][i + 1]) == 1)
		{
			dollar_var_to_expand(data, row, i);
			i = i + data->dollar_var_len;
			data->pos--;
		}
		else
			data->buffer[data->pos] = data->rl_dec[row][i];
		data->pos++;
		i++;
	}
	data->buffer[data->pos] = data->rl_dec[row][i];
	return (i);
}

int	move_index(t_vault *data, int row, int i)
{
	data->quote->quote_priority = data->rl_dec[row][i];
	data->buffer[data->pos] = data->rl_dec[row][i];
	i++;
	data->pos++;
	return (i);
}
