/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_analyzis2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbertin <mbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:57:20 by mbertin           #+#    #+#             */
/*   Updated: 2023/01/11 18:25:09 by mbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_multiple_chevron(t_vault *data)
{
	int	i;

	i = 0;
	while (data->read_line[i])
	{
		quote_iteration(data, &i);
		if (data->read_line[i] == '<' || data->read_line[i] == '>')
		{
			if ((data->read_line[i] == '<' && data->read_line[i + 1] == '>')
				|| (data->read_line[i] == '>' && data->read_line[i + 1] == '<'))
				return (FALSE);
			else if ((data->read_line[i] == '<'
					&& data->read_line[i + 1] == '<')
				|| (data->read_line[i] == '>' && data->read_line[i + 1] == '>'))
			{
				i++;
				if (data->read_line[i + 1] == '<'
					|| data->read_line[i + 1] == '>')
					return (FALSE);
			}
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
		i++;
		while (data->read_line[*i] != data->quote->quote_priority)
			i++;
		i++;
	}
}
