/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quote_management.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbertin <mbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:58:22 by mbertin           #+#    #+#             */
/*   Updated: 2022/11/29 09:47:03 by mbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	find_str_quote(t_vault *data)
{
	int		i;

	i = 0;
	data->quote_in->begin = 0;
	data->quote_in->len = 1;
	while (data->read_line[i])
	{
		if (data->read_line[i] == ' ')
		{
			while (data->read_line[i] == ' ')
				i++;
			data->quote_in->begin = i;
		}
		if (data->read_line[i] == '\"' || data->read_line[i] == '\'')
		{
			data->quote_in->quote = data->read_line[i];
			i++;
			while ((data->read_line[i] != data->quote_in->quote
					|| data->read_line[i + 1] > 32)
				&& data->read_line[i])
			{
				if (data->read_line[i] == data->quote_in->quote)
				{
					while (data->read_line[i] != ' ')
					{
						data->quote_in->len++;
						i++;
					}
					break ;
				}
				data->quote_in->len++;
				i++;
			}
			data->quote_in->len++;
			decomposer_array_to_replace(data, i);
		}
		i++;
	}
}

void	decomposer_array_to_replace(t_vault *data, int end)
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
			if (data->rl_decomp[i][j] == data->quote_in->quote)
			{
				replace_decomposer_array(data, end, &i);
				find_decomposer_to_switch(data, i);
				return ;
			}
			j++;
		}
		i++;
	}
}

void	replace_decomposer_array(t_vault *data, int end, int *i)
{
	int	j;

	j = 0;
	free(data->rl_decomp[*i]);
	data->rl_decomp[*i]
		= ft_calloc(sizeof(char), data->quote_in->len + 1);
	while (data->quote_in->begin <= end)
	{
		data->rl_decomp[*i][j]
			= data->read_line[data->quote_in->begin];
		data->quote_in->begin++;
		j++;
	}
	(*i)++;
	data->rl_decomp_i = *i;
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
			if (data->rl_decomp[next_array][j] == data->quote_in->quote)
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
