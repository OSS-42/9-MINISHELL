/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbertin <mbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:58:22 by mbertin           #+#    #+#             */
/*   Updated: 2023/01/12 16:56:39 by mbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	Je passe dans readline pour trouver une premiere quote.
	Quand je trouve une quote, je rentre dans la fonction len_of_replacement
	et je lui donne un pointeur sur mon index (car je vais avoir besoin
	qu'il continu de ce balader dans readline)
*/
void	find_str_quote(t_vault *data)
{
	int		i;

	i = 0;
	while (data->read_line[i])
	{
		data->spc_count = 0;
		if (data->read_line[i] == ' ')
		{
			while (data->read_line[i] == ' ')
				i++;
			data->quote->begin = i;
		}
		if (data->read_line[i] == '\"' || data->read_line[i] == '\'')
		{
			len_of_replacement(data, &i);
			if (data->spc_count != 0)
				find_decomposer_array_to_replace(data, i);
			data->quote->len_of_replacement = 0;
		}
		if (data->read_line[i])
			i++;
	}
	data->spc_count = 1;
}

/*
	Je reviens en arrière pour dans le cas ou il y aurait des caractere
	collé au quote. Je ravance dans readline pour trouver la quote de fermeture
	puis je continue d'avancer au cas ou il y aurait encore des caractères.
*/
void	len_of_replacement(t_vault *data, int *rl_index)
{
	begin_of_new_replacement(data, rl_index);
	while (data->read_line[*rl_index])
	{
		if (data->read_line[*rl_index] == data->quote->quote_priority)
		{
			(*rl_index)++;
			data->quote->len_of_replacement++;
			while ((data->read_line[*rl_index] != data->quote->quote_priority))
			{
				if (data->read_line[*rl_index] == ' ')
				{
					data->spc_count++;
					while (data->read_line[*rl_index] == ' ')
					{
						(*rl_index)++;
						data->quote->len_of_replacement++;
					}
					if (data->read_line[*rl_index] == data->quote->quote_priority)
					{
						(*rl_index)--;
						data->quote->len_of_replacement--;
					}
				}
				(*rl_index)++;
				data->quote->len_of_replacement++;
			}
			if (data->read_line[*rl_index + 1])
				len_after_quote(data, rl_index);
			else
				(*rl_index)++;
			break ;
		}
		data->quote->len_of_replacement++;
		(*rl_index)++;
	}
	data->quote->len_of_replacement++;
}

void	begin_of_new_replacement(t_vault *data, int *rl_index)
{
	data->quote->quote_priority = data->read_line[*rl_index];
	while (*rl_index != 0 && data->read_line[*rl_index] != ' ')
		(*rl_index)--;
	if (*rl_index != 0 || data->read_line[*rl_index] == ' ')
		(*rl_index)++;
	data->quote->begin = *rl_index;
}

void	len_after_quote(t_vault *data, int *rl_index)
{
	(*rl_index)++;
	data->quote->len_of_replacement++;
	while (data->read_line[*rl_index] && (data->read_line[*rl_index] != ' '))
	{
		if (data->read_line[*rl_index] == '\''
			|| data->read_line[*rl_index] == '\"')
		{
			data->quote->temp_priority = data->read_line[*rl_index];
			(*rl_index)++;
			data->quote->len_of_replacement++;
			while ((data->read_line[*rl_index] != data->quote->temp_priority))
			{
				if (data->read_line[*rl_index] == ' ')
					data->spc_count++;
				(*rl_index)++;
				data->quote->len_of_replacement++;
			}
		}
		data->quote->len_of_replacement++;
		(*rl_index)++;
	}
}
