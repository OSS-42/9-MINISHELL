/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 21:05:24 by ewurstei          #+#    #+#             */
/*   Updated: 2022/12/26 18:02:29 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_next_char(t_vault *data, int row, int i)
{
	if (data->rl_decomp[row][i + 1] == '\''
		|| data->rl_decomp[row][i + 1] == '\"')
	{
		i = i - 2;
		while (data->rl_decomp[row][i])
		{
			if (data->rl_decomp[row][i] != '\''
				|| data->rl_decomp[row][i] != '\"'
					|| data->rl_decomp[row][i] != '$')
				i++;
			data->buffer[data->pos] = data->rl_decomp[row][i];
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
	while (data->rl_decomp[row] && data->rl_decomp[row][i])
	{
		data->dollar_var_len = 0;
		if (ft_isinset(data->rl_decomp[row][i]) == 0)
			data->buffer[data->pos] = data->rl_decomp[row][i];
		else if (ft_isinset(data->rl_decomp[row][i]) == 1)
			i = sgle_quote_mngmt(data, row, i);
		else if (ft_isinset(data->rl_decomp[row][i]) == 2)
			i = dble_quote_mngmt(data, row, i);
		else if (ft_isinset(data->rl_decomp[row][i]) == 3)
		{
			dollar_var_to_extract(data, row, i);
			i = i + data->dollar_var_len;
			data->pos--;
		}
		i++;
		data->pos++;
	}
	free (data->rl_decomp[row]);
	data->rl_decomp[row] = ft_calloc(sizeof(char), ft_strlen(data->buffer) + 1);
	ft_strlcpy(data->rl_decomp[row], data->buffer, 500);
}

int	sgle_quote_mngmt(t_vault *data, int row, int i)
{
	i++;
	while (data->rl_decomp[row][i] && data->rl_decomp[row][i] != '\'')
	{
		data->buffer[data->pos] = data->rl_decomp[row][i];
		data->pos++;
		i++;
	}
	data->pos = data->pos - 1;
	return (i);
}

int	dble_quote_mngmt(t_vault *data, int row, int i)
{
	i++;
	while (data->rl_decomp[row][i] && data->rl_decomp[row][i] != '\"')
	{
		if (data->rl_decomp[row][i] == '$'
			&& ft_char_env_var(data->rl_decomp[row][i + 1]) == 1)
		{
			dollar_var_to_extract(data, row, i);
			i = i + data->dollar_var_len;
			data->pos--;
		}
		else
			data->buffer[data->pos] = data->rl_decomp[row][i];
		data->pos++;
		i++;
	}
	data->pos--;
	return (i);
}

// void	quote_priority(t_vault *data, int row)
// {
// 	int	j;

// 	j = 0;
// 	data->b_in->echo_priority = 0;
// 	while (data->rl_decomp[row] && data->rl_decomp[row][j] != '\0')
// 	{
// 		if (data->rl_decomp[row][j] == '\"')
// 		{
// 			data->b_in->echo_dble_q++;
// 			if (data->b_in->echo_first == 0)
// 				data->b_in->echo_first = 2;
// 			if (data->b_in->echo_dble_q % 2 == 0 && data->b_in->echo_first == 2)
// 				data->b_in->echo_priority = 34;
// 		}
// 		else if (data->rl_decomp[row][j] == '\'')
// 		{
// 			data->b_in->echo_sgle_q++;
// 			if (data->b_in->echo_first == 0)
// 				data->b_in->echo_first = 1;
// 			if (data->b_in->echo_sgle_q % 2 == 0 && data->b_in->echo_first == 1)
// 				data->b_in->echo_priority = 39;
// 		}
// 		j++;
// 	}
// 	return ;
// }