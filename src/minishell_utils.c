/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 23:09:55 by ewurstei          #+#    #+#             */
/*   Updated: 2022/12/02 23:24:03 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	spe_char(t_vault *data, int row)
{
	while (data->rl_decomp[row] && data->rl_decomp[row][0] != '\0')
	{
		data->b_in->echo_priority = quote_priority(data, row);
		if (data->b_in->echo_priority != 0)
			clean_quote(data, row);
		if (data->flag->dollar_count != 0 && data->b_in->echo_priority != 39)
			find_var_value(data, row);
		data->b_in->echo_first = 0;
		data->b_in->echo_priority = 0;
		row++;
	}
}

void	var_to_value(t_vault *data, int row, char *temp)
{
	int		i;
	int		j;
	int		k;

	j = -1;
	i = -1;
	while (data->rl_decomp[row][++j])
	{
		k = -1;
		if (data->rl_decomp[row][j] == '$' && data->flag->runs != 1)
		{
			while (data->dollar_var[++k])
				temp[++i] = data->dollar_var[k];
			data->flag->runs = 1;
			j = j + data->dollar_var_len;
			free (data->dollar_var);
		}
		else
		{
			temp[i] = data->rl_decomp[row][j];
			i++;
		}
	}
}
