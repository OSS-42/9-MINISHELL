/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quote_management.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbertin <mbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:58:22 by mbertin           #+#    #+#             */
/*   Updated: 2022/11/28 12:43:23 by mbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	double_quote_analyzis(t_vault *data)
{
	int	i;

	i = 0;
	data->double_quote_count = 0;
	while (data->read_line[i])
	{
		if (data->read_line[i] == '\"')
			data->double_quote_count++;
		i++;
	}
	if (data->double_quote_count % 2 != 0)
		printf("Wrong argument\n");
	return (data->double_quote_count);
}

void	find_str_doublequote(t_vault *data)
{
	int		i;
	int		begin;
	int		len;

	i = 0;
	begin = 0;
	len = 1;
	while (data->read_line[i])
	{
		if (data->read_line[i] == '\"')
		{
			begin = i;
			i++;
			while ((data->read_line[i] != '\"' || data->read_line[i + 1] > 32)
				&& data->read_line[i])
			{
				len++;
				i++;
			}
			len++;
			replace_decomposer_array(data, len, begin, i);
		}
		i++;
	}
}

void	replace_decomposer_array(t_vault *data, int len, int begin, int end)
{
	int		i;
	int		j;

	if (data->rl_decomp_i != 0)
		i = data->rl_decomp_i;
	else
		i = 0;
	while (data->rl_decomp[i])
	{
		j = 0;
		while (data->rl_decomp[i][j])
		{
			if (data->rl_decomp[i][j] == '\"')
			{
				free(data->rl_decomp[i]);
				data->rl_decomp[i] = ft_calloc(sizeof(char), len + 1);
				j = 0;
				while (begin <= end)
				{
					data->rl_decomp[i][j] = data->read_line[begin];
					begin++;
					j++;
				}
				i++;
				data->rl_decomp_i = i;
				find_decomposer_to_switch(data, i);
				return ;
			}
			j++;
		}
		i++;
	}
}

void	find_decomposer_to_switch(t_vault *data, int to_switch)
{
	int	next_array;
	int	actual_array;
	int	j;

	next_array = to_switch;
	actual_array = to_switch;
	j = 0;
	while (data->rl_decomp[next_array])
	{
		while (data->rl_decomp[next_array][j])
		{
			if (data->rl_decomp[next_array][j] == '\"')
			{
				next_array++;
				switch_decomposer(data, &next_array, &actual_array);
				return ;
			}
			j++;
		}
		j = 0;
		next_array++;
	}
}

void	switch_decomposer(t_vault *data, int *next_array, int *actual_array)
{
	while (data->rl_decomp[*next_array])
	{
		data->rl_decomp[*actual_array] = data->rl_decomp[*next_array];
		(*next_array)++;
		(*actual_array)++;
	}
	while (data->rl_decomp[*actual_array])
	{
		data->rl_decomp[*actual_array] = "\0";
		(*actual_array)++;
	}
}
