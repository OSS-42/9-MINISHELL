/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 23:09:55 by ewurstei          #+#    #+#             */
/*   Updated: 2022/12/05 11:45:38 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	spe_char(t_vault *data, int row)
{
	int	j;

	j = 0;
	row += 1;
	while (data->rl_decomp[row][j] != '\0')
	{
		printf("%d\n", j);
		if (data->rl_decomp[row][j] == '$')
			data->flag->dollar_count++;
		j++;
	}
	printf("%d\n", data->flag->dollar_count);
	while (data->rl_decomp[row] && data->rl_decomp[row][0] != '\0')
	{
		data->b_in->echo_priority = quote_priority(data, row);
		if (data->b_in->echo_priority != 0)
			clean_quote(data, row);
		if (data->flag->dollar_count != 0 && data->b_in->echo_priority != 39)
			find_var_value(data, row);
		if (data->flag->dollar_count > 1)
			split_on_dollar(data, row);
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

	j = 0;
	i = 0;
	while (data->rl_decomp[row][j])
	{
		k = 0;
		if (data->rl_decomp[row][j] == '$' && data->flag->runs != 1)
		{
			while (data->dollar_var[k])
			{
				temp[i] = data->dollar_var[k];
				k++;
				i++;
			}
			data->flag->runs = 1;
			j = j + data->dollar_var_len;
			free (data->dollar_var);
		}
		else
		{
			temp[i] = data->rl_decomp[row][j];
			i++;
		}
		j++;
	}
}

void	split_on_dollar(t_vault *data, int row)
{
	if (ft_strchr(data->rl_decomp[row], '$') == 1 && data->flag->dollar_count > 1)
		data->split_dollar = ft_split(data->rl_decomp[row], '$');
	print_double_array(data->split_dollar);
}
