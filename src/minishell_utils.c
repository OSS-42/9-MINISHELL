/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 23:09:55 by ewurstei          #+#    #+#             */
/*   Updated: 2022/12/06 21:14:54 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	spe_char(t_vault *data, int row)
{
	int	j;

	while (data->rl_decomp[row] && data->rl_decomp[row][0] != '\0')
	{
		j = 0;
		data->flag->dollar_count = 0;
		while (data->rl_decomp[row][j] != '\0')
		{
			if (data->rl_decomp[row][j] == '$')
				data->flag->dollar_count++;
			j++;
		}
		data->b_in->echo_priority = quote_priority(data, row);
		if (data->b_in->echo_priority != 0)
			clean_quote(data, row);
		if (data->flag->dollar_count > 1
			&& ft_strchr(data->rl_decomp[row], '$') != NULL)
			split_on_dollar(data, row);
		if (data->flag->dollar_count != 0 && data->b_in->echo_priority != 39)
			find_var_value(data, row);
		reset_counters(data);
		row++;
	}
}

void	reset_counters(t_vault *data)
{
//	if (data->dollar_var)
//		free (data->dollar_var);
	data->dollar_var_len = 0;
	data->flag->runs = 0;
	data->b_in->echo_first = 0;
	data->b_in->echo_priority = 0;
}
