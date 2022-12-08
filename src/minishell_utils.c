/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 23:09:55 by ewurstei          #+#    #+#             */
/*   Updated: 2022/12/07 22:55:21 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_row(t_vault *data, int row)
{
	if (data->b_in->first_word == 1)
	{
		ft_putstr_fd(data->rl_decomp[row], 1);
		data->b_in->first_word = 0;
	}
	else if (data->flag->same_line >= 1)
	{
		ft_putstr_fd(data->rl_decomp[row], 1);
		data->flag->same_line--;
	}
	else
	{
		ft_putstr_fd(" ", 1);
		ft_putstr_fd(data->rl_decomp[row], 1);
	}
	return ;
}

void	spe_char(t_vault *data, int row)
{

// voir a splitter sur le char qui vient en premier (echo->first)
	while (data->rl_decomp[row] && data->rl_decomp[row][0] != '\0')
	{
//		rl_decomp_char_count(data, row, '$');
		if (data->rl_decomp[row])
		{
			print_double_array(data->rl_decomp);
			data->b_in->echo_priority = quote_priority(data, row);
			printf("%d\n", data->b_in->echo_priority);
			printf("%d\n", data->b_in->echo_first);
			printf("%d\n", data->flag->dollar_count);
			if (data->flag->dollar_count > 1)
				split_on_char(data, row, '$');
			if (data->b_in->echo_priority != 0)
				clean_quote(data, row);
			if (data->flag->dollar_count != 0 && data->b_in->echo_priority != 39)
				find_var_value(data, row);
			row++;
		}
		reset_counters(data);
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
	data->flag->dollar_count = 0;
}

void	rl_decomp_char_count(t_vault *data, int row, char c)
{
	int	i;

	i = 0;
	data->flag->dollar_count = 0;
	while (data->rl_decomp[row][i] != '\0')
	{
		if (data->rl_decomp[row][i] == c)
			data->flag->dollar_count++;
		i++;
	}
	return ;
}
