/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 23:09:55 by ewurstei          #+#    #+#             */
/*   Updated: 2022/12/13 17:03:57 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_row(t_vault *data)
{
	if (data->b_in->first_word == 1 || data->b_in->echo_flag_n == 1)
	{
		ft_putstr_fd(data->buffer, 1);
		data->b_in->first_word = 0;
	}
	else
	{
		ft_putstr_fd(" ", 1);
		ft_putstr_fd(data->buffer, 1);
	}
	if (data->b_in->first_word == 0)
	{
		data->b_in->echo_forget_minus = 1;
	 	data->b_in->echo_flag_n = 0;
	}
	return ;
}

int	ft_isinset(char c)
{
	if (c == '\'')
		return (1);
	else if (c == '\"')
		return (2);
	else if (c == '$')
		return (3);
	else if (c == '-')
		return (4);
	else
		return (0);
}

int	echo_sgle_quote(t_vault *data, int row, int i)
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

int	echo_dble_quote(t_vault *data, int row, int i)
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

void	echo_parse_row(t_vault *data, int row)
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
			i = echo_sgle_quote(data, row, i);
		else if (ft_isinset(data->rl_decomp[row][i]) == 2)
			i = echo_dble_quote(data, row, i);
		else if (ft_isinset(data->rl_decomp[row][i]) == 3
			&& ft_char_env_var(data->rl_decomp[row][i + 1]) == 1)
		{
			dollar_var_to_extract(data, row, i);
			i = i + data->dollar_var_len;
			data->pos--;
		}
		else if (ft_isinset(data->rl_decomp[row][0]) == 4)
			i = echo_minus(data, row, i + 1);
		i++;
		data->pos++;
	}
}
