/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbertin <mbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:58:22 by mbertin           #+#    #+#             */
/*   Updated: 2022/12/08 08:51:57 by mbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	Je passe dans readline pour trouver une premiere quote.
	Quand je trouve une quote, je rentre dans la fonction len_of_replacement
	et je lui donne un pointeur sur mon index (car je vais avoir besoin qu'il continu
	de ce balader dans readline)
*/
void	find_str_quote(t_vault *data)
{
	int		i;

	i = 0;
	data->quote_in->begin = 0;
	data->quote_in->len = 1;
	while (data->read_line[i])
	{
		data->quote_in->spc_count = 0;
		if (data->read_line[i] == ' ')
		{
			while (data->read_line[i] == ' ')
				i++;
			data->quote_in->begin = i;
		}
		if (data->read_line[i] == '\"' || data->read_line[i] == '\'')
		{
			len_of_replacement(data, &i);
			find_decomposer_array_to_replace(data, i);
		}
		i++;
	}
}

/*
	Je continue d'avancer dans readline pour trouver la quote de fermeture
	et calculer la longueur de la string qui va remplacer la ligne de rl_decomp.
*/
void	len_of_replacement(t_vault *data, int *rl_index)
{
	data->quote_in->quote = data->read_line[*rl_index];
	(*rl_index)++;
	while ((data->read_line[*rl_index] != data->quote_in->quote
			|| data->read_line[*rl_index + 1] > 32)
		&& data->read_line[*rl_index])
	{
		if (data->read_line[*rl_index] == data->quote_in->quote)
		{
			while (data->read_line[*rl_index]
				&& data->read_line[*rl_index] != ' ')
			{
				data->quote_in->len++;
				(*rl_index)++;
			}
			break ;
		}
		if (data->read_line[*rl_index] == ' ')
			data->quote_in->spc_count++;
		data->quote_in->len++;
		(*rl_index)++;
	}
	data->quote_in->len++;
}

void	find_decomposer_array_to_replace(t_vault *data, int end)
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
	if (ft_strchr(data->rl_decomp[*i - 1], ' ') != NULL)
		find_decomposer_to_switch(data, *i);
}

void	find_decomposer_to_switch(t_vault *data, int to_switch)
{
	int	next_array;
	int	actual_array;

	next_array = to_switch + data->quote_in->spc_count;
	actual_array = to_switch;
	while (data->rl_decomp[next_array])
	{
		free (data->rl_decomp[actual_array]);
		data->rl_decomp[actual_array] = ft_strdup(data->rl_decomp[next_array]);
		next_array++;
		actual_array++;
	}
	data->rl_decomp[actual_array][0] = '\0';
	data->quote_in->spc_count = 0;
}
