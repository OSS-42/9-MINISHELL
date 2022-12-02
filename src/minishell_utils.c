/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 23:09:55 by ewurstei          #+#    #+#             */
/*   Updated: 2022/12/02 08:36:08 by ewurstei         ###   ########.fr       */
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

void	swap_lines(t_vault *data, int rows)
{
	int	i;
	int	j;

	i = -1;
	while (++i < rows)
	{
		j = i;
		while (++j < rows)
		{
			if (ft_strcmp(data->b_in->env_ord[i], data->b_in->env_ord[j]) > 0)
			{
				data->b_in->order_var = ft_strdup(data->b_in->env_ord[i]);
				data->b_in->env_ord[i] = ft_strdup(data->b_in->env_ord[j]);
				data->b_in->env_ord[j] = ft_strdup(data->b_in->order_var);
			}
		}
	}
	return ;
}
