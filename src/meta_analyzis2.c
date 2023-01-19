/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_analyzis2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momo <momo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:57:20 by mbertin           #+#    #+#             */
/*   Updated: 2023/01/18 11:52:59 by momo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_wrong_redirection(t_vault *data)
{
	if (pipe_after_chevron(data, 0) == FALSE)
		return (FALSE);
	if (opposite_chevron(data, 0) == FALSE)
		return (FALSE);
	if (triple_chevron(data, 0) == FALSE)
		return (FALSE);
	if (chevron_space_chevron(data, 0) == FALSE)
		return (FALSE);
	return (TRUE);
}

void	quote_iteration(t_vault *data, int *i)
{
	if (data->read_line[*i] == '\'' || data->read_line[*i] == '\"')
	{
		data->quote->quote_priority = data->read_line[*i];
		(*i)++;
		while (data->read_line[*i] != data->quote->quote_priority)
			(*i)++;
	}
}

int	pipe_after_chevron(t_vault *data, int i)
{
	while (data->read_line[i])
	{
		quote_iteration(data, &i);
		if (data->read_line[i] == '<' || data->read_line[i] == '>')
		{
			i++;
			if (data->read_line[i] == '<' || data->read_line[i] == '>')
				i++;
			if (!data->read_line[i])
				return (FALSE);
			while (data->read_line[i] == ' ')
				i++;
			if (data->read_line[i] == '|')
				return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

int	triple_chevron(t_vault *data, int i)
{
	while (data->read_line[i])
	{
		quote_iteration(data, &i);
		if (data->read_line[i] == '<' || data->read_line[i] == '>')
		{
			data->flag->chevron = data->read_line[i];
			if (data->read_line[i + 1] && data->read_line[i + 2]
				&& data->read_line[i + 1] == data->flag->chevron
				&& data->read_line[i + 2] == data->flag->chevron)
				return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

int	opposite_chevron(t_vault *data, int i)
{
	while (data->read_line[i])
	{
		quote_iteration(data, &i);
		if ((data->read_line[i] == '<' && !data->read_line[i + 1])
			|| (data->read_line[i] == '<' && data->read_line[i + 1] == '>')
			|| (data->read_line[i] == '>' && data->read_line[i + 1] == '<'))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	chevron_space_chevron(t_vault *data, int i)
{
	while (data->read_line[i])
	{
		quote_iteration(data, &i);
		if (data->read_line[i] == '<' || data->read_line[i] == '>')
		{
			if (data->read_line[i + 1] && data->read_line[i + 1] == ' ')
			{
				i++;
				if (data->read_line[i + 1]
					&& (data->read_line[i + 1] == '<'
						|| data->read_line[i + 1] == '>'))
					return (FALSE);
			}
		}
		i++;
	}
	return (TRUE);
}
