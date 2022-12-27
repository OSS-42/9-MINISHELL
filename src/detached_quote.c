/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detached_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 08:48:00 by mbertin           #+#    #+#             */
/*   Updated: 2022/12/27 14:02:50 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	Je me balade dans rl_dec grace a une boucle. Je cherche les lignes qui
	contiennent des quotes. Quand c'est le cas je regarde si il y à quelque
	chose de collé au début de ces quotes. Si c'est le cas j'augment de un len.
	Meme chose à la fin des quotes.
*/

void	detached_quote_tab(t_vault *data)
{
	char	**buffer;
	int		len;

	buffer = data->rl_dec;
	len = len_detached_quote_tab(data);
	data->rl_dec = ft_dbl_ptr_realloc(data->rl_dec, len + 1);
	fill_detached_quote_tab(data, buffer);
}

int	len_detached_quote_tab(t_vault *data)
{
	int	row;
	int	line;
	int	len;

	row = 0;
	len = 0;
	while (data->rl_dec[row] && data->rl_dec[row][0])
	{
		line = 0;
		while (data->rl_dec[row][line])
		{
			if (data->rl_dec[row][line] == '\''
				|| data->rl_dec[row][line] == '\"')
				quote_to_quote(data, row, &line, &len);
			line++;
		}
		row++;
		len++;
	}
	return (len);
}

void	quote_to_quote(t_vault *data, int row, int *line, int *len)
{
	data->quote->quote_priority = data->rl_dec[row][*line];
	if (data->rl_dec[row][*line - 1] != ' ' && data->rl_dec[row][*line - 1])
		(*len)++;
	(*line)++;
	while (data->rl_dec[row][*line] != data->quote->quote_priority)
		(*line)++;
	if (data->rl_dec[row][*line + 1]
		&& data->rl_dec[row][*line + 1] != ' ')
	{
		(*len)++;
		(*line)++;
		while (data->rl_dec[row][(*line)++])
		{
			if (data->rl_dec[row][*line] == '\''
				|| data->rl_dec[row][*line] == '\"')
			{
				data->quote->quote_priority = data->rl_dec[row][*line];
				(*line)++;
				while (data->rl_dec[row][*line]
					!= data->quote->quote_priority)
					(*line)++;
				(*len)++;
			}
		}
	}
}

void	fill_detached_quote_tab(t_vault *data, char **buffer)
{
	int	row;
	int	line;
	int	i;
	int	j;

	row = 0;
	i = 0;
	j = 0;
	while (buffer[row] && buffer[row][0])
	{
		line = 0;
		if (ft_strchr(buffer[row], '\'') == NULL && ft_strchr(buffer[row], '\"') == NULL)
			data->rl_dec[i++] = ft_strdup(buffer[row]);
		else
		{
			while (buffer[row][line])
			{
				if (buffer[row][line] != '\'' && buffer[row][line] != '\"')
				{
					data->rl_dec[i] = ft_calloc(sizeof(char), len_out_quote_dtch(buffer[row], line) + 1);
					while (buffer[row][line] && buffer[row][line] != '\'' && buffer[row][line] != '\"')
					{
						data->rl_dec[i][j] = buffer[row][line];
						j++;
						line++;
					}
					j = 0;
					i++;
				}
				else if (buffer[row][line] == '\'' || buffer[row][line] == '\"')
				{
					data->rl_dec[i] = ft_calloc(sizeof(char), len_in_quote_dtch(data, buffer[row], line) + 1);
					data->quote->quote_priority = buffer[row][line];
					data->rl_dec[i][j] = buffer[row][line];
					line++;
					j++;
					while (buffer[row][line] != data->quote->quote_priority)
					{
						data->rl_dec[i][j] = buffer[row][line];
						j++;
						line++;
					}
					data->rl_dec[i][j] = buffer[row][line];
					line++;
					i++;
					j = 0;
				}
			}
		}
		row++;
	}
}
 //echo bonjour | cat -e |" wc"| "cat -e"