/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detached_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbertin <mbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 08:48:00 by mbertin           #+#    #+#             */
/*   Updated: 2022/12/27 10:54:49 by mbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	Je me balade dans rl_decomp grace a une boucle. Je cherche les lignes qui
	contiennent des quotes. Quand c'est le cas je regarde si il y à quelque
	chose de collé au début de ces quotes. Si c'est le cas j'augment de un len.
	Meme chose à la fin des quotes.
*/
void	detached_quote_tab(t_vault *data)
{
	int	row;
	int	line;
	int	len;

	row = 0;
	len = 0;
	while (data->rl_decomp[row] && data->rl_decomp[row][0])
	{
		line = 0;
		while (data->rl_decomp[row][line])
		{
			if (data->rl_decomp[row][line] == '\''
				|| data->rl_decomp[row][line] == '\"')
				quote_to_quote(data, row, &line, &len);
			line++;
		}
		row++;
		len++;
	}
	printf("len : %d\n", len);
}

void	quote_to_quote(t_vault *data, int row, int *line, int *len)
{
	data->quote->quote_priority = data->rl_decomp[row][*line];
	if (data->rl_decomp[row][*line - 1] != ' ' && data->rl_decomp[row][*line - 1])
		(*len)++;
	(*line)++;
	while (data->rl_decomp[row][*line] != data->quote->quote_priority)
		(*line)++;
	if (data->rl_decomp[row][*line + 1]
		&& data->rl_decomp[row][*line + 1] != ' ')
	{
		(*len)++;
		(*line)++;
		while (data->rl_decomp[row][(*line)++])
		{
			if (data->rl_decomp[row][*line] == '\''
				|| data->rl_decomp[row][*line] == '\"')
			{
				data->quote->quote_priority = data->rl_decomp[row][*line];
				(*line)++;
				while (data->rl_decomp[row][*line]
					!= data->quote->quote_priority)
					(*line)++;
				(*len)++;
			}
		}
	}
}
