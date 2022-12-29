/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detached_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbertin <mbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 08:48:00 by mbertin           #+#    #+#             */
/*   Updated: 2022/12/29 10:58:40 by mbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	detached_quote_tab(t_vault *data)
{
	int		len;

	len = len_detached_quote_tab(data); //Mauvais len avec echo "test 9">"test">"test1">"test2"
	data->temp = ft_calloc(sizeof(char *), len + 1);
	fill_detached_quote_tab(data);
	data->rl_dec = ft_dbl_ptr_copy(data->temp);
}

int	len_detached_quote_tab(t_vault *data)
{
	int		row;
	int		line;
	int		len;

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
			if (line < (int)ft_strlen(data->rl_dec[row]))
				line++;
			else
				break ;
		}
		row++;
		len++;
	}
	return (len);
}

void	quote_to_quote(t_vault *data, int row, int *line, int *len)
{
	data->quote->quote_priority = data->rl_dec[row][*line];
	if (*line > 0 && data->rl_dec[row][*line - 1] != ' ')
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
			else
				(*len)++;
		}
	}
}

void	fill_detached_quote_tab(t_vault *data)
{
	int	row;
	int	line;
	int	i;

	row = 0;
	i = 0;
	while (data->rl_dec[row] && data->rl_dec[row][0])
	{
		line = 0;
		if (ft_strchr(data->rl_dec[row], '\'') == NULL
			&& ft_strchr(data->rl_dec[row], '\"') == NULL)
			data->temp[i++] = ft_strdup(data->rl_dec[row]);
		else
			row_with_quote(data, &i, row, &line);
		free (data->rl_dec[row]);
		row++;
	}
}

void	row_with_quote(t_vault *data, int *i, int row, int *line)
{
	while (data->rl_dec[row][*line])
	{
		if (data->rl_dec[row][*line] != '\''
			&& data->rl_dec[row][*line] != '\"')
			fill_out_quote(data, i, row, line);
		else if (data->rl_dec[row][*line] == '\''
			|| data->rl_dec[row][*line] == '\"')
			fill_in_quote(data, i, row, line);
	}
}
