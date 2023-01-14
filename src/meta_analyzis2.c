/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_analyzis2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maison <maison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:57:20 by mbertin           #+#    #+#             */
/*   Updated: 2023/01/14 11:04:18 by maison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_wrong_redirection(t_vault *data)
{
	int	i;

	i = 0;
	while (data->read_line[i])
	{
		quote_iteration(data, &i);
		if (data->read_line[i] == '<' || data->read_line[i] == '>')
		{
			if (pipe_after_chevron(data, &i) == FALSE)
				return (FALSE);
			else if ((data->read_line[i] == '<' && data->read_line[i + 1] == '>')
				|| (data->read_line[i] == '>' && data->read_line[i + 1] == '<'))
				return (FALSE);
			else if (triple_chevron(data, &i) == FALSE)
				return (FALSE);
			else if (!data->read_line[i + 1])
				return (FALSE);
		}
		if (data->read_line[i])
			i++;
	}
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

int	pipe_after_chevron(t_vault *data, int *i)
{
	if (data->read_line[*i + 1] == data->read_line[*i]
			&& data->read_line[*i + 2] == '|')
		return (FALSE);
	else if (data->read_line[*i + 1] == data->read_line[*i]
			&& data->read_line[*i + 2] == ' ')
	{
		*i = *i + 2;
		while (data->read_line[*i] == ' ')
			(*i)++;
		if (data->read_line[*i] && data->read_line[*i] == '|')
			return (FALSE);
	}
	else if (data->read_line[*i + 1] == ' ')
	{
		(*i)++;
		while (data->read_line[*i] == ' ')
			(*i)++;
		if (data->read_line[*i] && data->read_line[*i] == '|')
			return (FALSE);
	}
	return (TRUE);
}

int triple_chevron(t_vault *data, int *i)
{
	if ((data->read_line[*i] == '<' && data->read_line[*i + 1] == '<')
		|| (data->read_line[*i] == '>' && data->read_line[*i + 1] == '>'))
	{
		(*i)++;
		if (data->read_line[*i + 1] == '<'
			|| data->read_line[*i + 1] == '>')
			return (FALSE);
	}
	return (TRUE);
}