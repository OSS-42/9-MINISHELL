/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detached_quote_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbertin <mbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 12:28:30 by mbertin           #+#    #+#             */
/*   Updated: 2022/12/27 12:33:21 by mbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	len_out_quote_dtch(char *rl_dec, int line)
{
	int	len;

	len = 0;
	while (rl_dec[line] && rl_dec[line] != '\'' && rl_dec[line] != '\"')
	{
		line++;
		len++;
	}
	return (len);
}

int	len_in_quote_dtch(t_vault *data, char *rl_dec, int line)
{
	int	len;

	len = 1;
	data->quote->quote_priority = rl_dec[line];
	line++;
	while (rl_dec[line++] != data->quote->quote_priority)
		len++;
	len++;
	return (len);
}

// void	fill_out_quote(t_vault *data, int *i, int row, int *line)
// {
// 	int	j;

// 	j = 0;
// 	data->rl_dec[*i] = ft_calloc(sizeof(char),
// 		len_out_quote_dtch(buffer[row], line) + 1);
// 	while (buffer[row][line] && buffer[row][line] != '\'' && buffer[row][line] != '\"')
// 	{
// 		data->rl_dec[*i][j] = buffer[row][line];
// 		j++;
// 		line++;
// 	}
// 	i++;
// }