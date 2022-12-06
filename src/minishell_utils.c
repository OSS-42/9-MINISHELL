/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 23:09:55 by ewurstei          #+#    #+#             */
/*   Updated: 2022/12/05 22:39:27 by ewurstei         ###   ########.fr       */
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
		if (data->flag->dollar_count > 1 && ft_strchr(data->rl_decomp[row], '$') != NULL)
			split_on_dollar(data, row);
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
	int		i;
	int		m;
	char	**temp;

	i = 0;
	temp = NULL;
	data->split_dollar = ft_split(data->rl_decomp[row], '$');
	data->flag->dollar_split = 1;
	while (data->split_dollar[i])
	{
		data->split_dollar[i] = ft_strjoin("$", data->split_dollar[i]);
		// printf("#%d : %s\n", i, data->split_dollar[i]);
		i++;
	}
	i = 0;
	temp = ft_calloc(sizeof(char *), ft_dbl_ptr_len(data->rl_decomp) + ft_dbl_ptr_len(data->split_dollar));
	while (i < row)
	{
		temp[i] = ft_strdup(data->rl_decomp[i]);
		// printf("temp[%d] : %s\n", i, temp[i]);
		i++;
	}
	m = 0;
	while (m < data->flag->dollar_count)
	{
		temp[i] = ft_strdup(data->split_dollar[m]);
		// printf("temp[%d] : %s\n", i, temp[i]);
		i++;
		m++;
	}
	while (i < ft_dbl_ptr_len(data->rl_decomp) && data->rl_decomp[i + 1])
	{
		temp[i] = ft_strdup(data->rl_decomp[i + 1]);
		// printf("temp[%d] : %s\n", i, temp[i]);
		i++;
	}
	data->rl_decomp = ft_dbl_ptr_realloc(data->rl_decomp, i + 1);
	i = 0;
	while (temp[i])
	{
		data->rl_decomp[i] = ft_strdup(temp[i]);
		free (temp[i]);
		i++;
	}
	free (temp);
	return ;
}
