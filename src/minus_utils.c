/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 15:10:45 by ewurstei          #+#    #+#             */
/*   Updated: 2022/12/16 15:11:04 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	recreate_arg_tab(t_vault *data, char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free (data->rl_decomp[i]);
		data->rl_decomp[i] = ft_strdup(tab[i]);
		free (tab[i]);
		i++;
	}
	data->rl_decomp[i] = NULL;
	free (tab);
}

char	**create_temp_swap(t_vault *data, int row)
{
	int		i;
	int		line;
	char	**temp_swap;

	temp_swap = ft_calloc(sizeof(char *), ft_dbl_ptr_len(data->rl_decomp));
	i = 0;
	line = 0;
	while (data->rl_decomp[line])
	{
		if (line == row)
			line++;
		if (data->rl_decomp[line])
			temp_swap[i] = ft_strdup(data->rl_decomp[line]);
		else
		{
			temp_swap[i] = NULL;
			break ;
		}
		line++;
		i++;
	}
	return (temp_swap);
}

void	check_minus_validity(t_vault *data, int row, int i)
{
	while (data->rl_decomp[row][i] == '-' && data->rl_decomp[row][i])
			i++;
	if (i > 1 || data->b_in->echo_forget_minus == 1)
	{
		data->b_in->echo_forget_minus = 1;
		data->b_in->dont_do_minus = 1;
		return ;
	}
	else
	{
		while (data->rl_decomp[row][i])
		{
			if (data->rl_decomp[row][i] != 'n')
			{
				data->b_in->echo_forget_minus = 1;
				data->b_in->dont_do_minus = 1;
				break ;
			}
			else
				data->b_in->echo_forget_minus = 0;
			i++;
		}
	}
}

void	parse_minus(t_vault *data)
{
	int		row;
	int		i;
	char	**temp_swap;

	row = 1;
	i = 0;
	while (data->rl_decomp[row] && data->rl_decomp[row][i])
	{
		check_minus_validity(data, row, i);
		if (data->b_in->echo_forget_minus == 0 && data->rl_decomp[row + 1])
		{
			temp_swap = create_temp_swap(data, row);
			ft_dbl_ptr_realloc(data->rl_decomp, ft_dbl_ptr_len(temp_swap));
			recreate_arg_tab(data, temp_swap);
			data->b_in->echo_flag_n = 1;
			data->b_in->echo_minus_n = 1;
			row = row - 1;
		}
		row++;
		i = 0;
	}
}
