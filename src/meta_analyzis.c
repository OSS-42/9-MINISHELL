/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_analyzis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbertin <mbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 10:05:10 by mbertin           #+#    #+#             */
/*   Updated: 2022/11/29 10:13:02 by mbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	meta_analyzis(t_vault *data)
{
	int	i;

	i = 0;
	data->quote_in->double_quote_count = 0;
	data->quote_in->simple_quote_count = 0;
	while (data->read_line[i])
	{
		if (data->read_line[i] == '\"')
			data->quote_in->double_quote_count++;
		else if (data->read_line[i] == '\'')
			data->quote_in->simple_quote_count++;
		i++;
	}
// savoir lequel vient en premier pour valider la paire
	if (data->quote_in->double_quote_count % 2 != 0)
		printf("Wrong argument\n");
	return (data->quote_in->double_quote_count);
}
