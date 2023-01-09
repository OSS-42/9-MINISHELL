/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbertin <mbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 15:10:45 by ewurstei          #+#    #+#             */
/*   Updated: 2023/01/09 14:07:44 by mbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	recreate_arg_tab(t_vault *data, char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free (data->cmd->opt[i]);
		data->cmd->opt[i] = ft_strdup(tab[i]);
		free (tab[i]);
		i++;
	}
	data->cmd->opt[i] = NULL;
	free (tab);
}

char	**create_temp_swap(t_vault *data, int row)
{
	int		i;
	int		line;
	char	**temp_swap;

	temp_swap = ft_calloc(sizeof(char *), ft_dbl_ptr_len(data->cmd->opt));
	i = 0;
	line = 0;
	while (data->cmd->opt[line])
	{
		if (line == row)
			line++;
		if (data->cmd->opt[line])
			temp_swap[i] = ft_strdup(data->cmd->opt[line]);
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
	while (data->cmd->opt[row][i] == '-' && data->cmd->opt[row][i])
			i++;
	if (i > 1 || data->b_in->forget_minus == 1)
	{
		data->b_in->forget_minus = 1;
		data->b_in->dont_do_minus = 1;
		return ;
	}
	else
	{
		while (data->cmd->opt[row][i])
		{
			if (data->cmd->opt[row][i] != 'n')
			{
				data->b_in->forget_minus = 1;
				data->b_in->dont_do_minus = 1;
				break ;
			}
			else
				data->b_in->forget_minus = 0;
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
	while (data->cmd->opt[row] && data->cmd->opt[row][i])
	{
		check_minus_validity(data, row, i);
		if (data->b_in->forget_minus == 0)
		{
			temp_swap = create_temp_swap(data, row);
			ft_dbl_ptr_free((void **)data->cmd->opt);
			data->cmd->opt = ft_calloc(sizeof (char *),
					ft_dbl_ptr_len(temp_swap));
			recreate_arg_tab(data, temp_swap);
			data->b_in->echo_flag_n = 1;
			data->b_in->minus_n = 1;
			row = row - 1;
		}
		row++;
		i = 0;
	}
}
