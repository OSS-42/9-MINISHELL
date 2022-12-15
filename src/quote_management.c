/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momo <momo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 11:58:22 by mbertin           #+#    #+#             */
/*   Updated: 2022/12/14 20:02:03 by momo             ###   ########.fr       */
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
			printf("%d\n", data->quote->len_of_replacement);
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
	Je reviens en arrière pour dans le cas ou il y aurait des caractere collé au quote.
	Je ravance dans readline pour trouver la quote de fermeture puis je continue d'avancer
	au cas ou il y aurait encore des caractères.
*/
void	len_of_replacement(t_vault *data, int *rl_index)
{
	data->quote->quote_priority = data->read_line[*rl_index];
	while (*rl_index != 0 && data->read_line[*rl_index] != ' ')
		(*rl_index)--;
	if (*rl_index != 0)
		(*rl_index)++;
	while (data->read_line[*rl_index])
	{
		if (data->read_line[*rl_index] == data->quote->quote_priority)
		{
			(*rl_index)++;
			data->quote->len_of_replacement++;
			while ((data->read_line[*rl_index] != data->quote->quote_priority))
			{
				(*rl_index)++;
				data->quote->len_of_replacement++;
				if (data->read_line[*rl_index] == ' ')
					data->spc_count++;
			}
			while (data->read_line[*rl_index] && (data->read_line[*rl_index] != ' '))
			{
				(*rl_index)++;
				data->quote->len_of_replacement++;
			}
			data->quote->len_of_replacement--;
			break;
		}
		data->quote->len_of_replacement++;
		(*rl_index)++;
	}
	data->quote->len_of_replacement++;
}


/*
	Je cherche la ligne à remplacer dans rl_decomp en trouvant la quote
	prioritaire que j'ai trouvé dans readline
*/
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
			if (data->rl_decomp[i][j] == data->quote->quote_priority)
			{
				replace_decomposer_array(data, end, &i);
				return ;
			}
			j++;
		}
		i++;
	}
}

/*
	Je free la ligne de rl_decomp à remplacer, je la calloc de la taille de
	la nouvelle ligne qui va la remplacer et je me balade dans readline, de
	begin jusqu'a end, pour remplir la nouvelle ligne.
*/
void	replace_decomposer_array(t_vault *data, int end, int *i)
{
	int	j;

	j = 0;
	free(data->rl_decomp[*i]);
	data->rl_decomp[*i]
		= ft_calloc(sizeof(char), data->quote->len_of_replacement + 1);
	while (data->quote->begin <= end)
	{
		data->rl_decomp[*i][j]
			= data->read_line[data->quote->begin];
		data->quote->begin++;
		j++;
	}
	(*i)++;
	data->rl_decomp_i = *i;
	if (ft_strchr(data->rl_decomp[*i - 1], ' ') != NULL)
		find_decomposer_to_switch(data, *i);
}

/*
	Je décalle les éléments du tableau. spc_count va me servir à savoir
	combien de ligne je vais devoir sauter dans rl_decomp pour commencer
	mon remplacement.
*/
void	find_decomposer_to_switch(t_vault *data, int to_switch)
{
	int	next_array;
	int	actual_array;

	next_array = to_switch + data->spc_count;
	actual_array = to_switch;
	while (data->rl_decomp[next_array])
	{
		free (data->rl_decomp[actual_array]);
		data->rl_decomp[actual_array] = ft_strdup(data->rl_decomp[next_array]);
		next_array++;
		actual_array++;
	}
	if (data->rl_decomp[actual_array])
		data->rl_decomp[actual_array][0] = '\0';
}
