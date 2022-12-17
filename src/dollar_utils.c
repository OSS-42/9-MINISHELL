/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:21:56 by ewurstei          #+#    #+#             */
/*   Updated: 2022/12/16 19:49:27 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	quote_priority(t_vault *data, int row)
{
	int	j;

	j = 0;
	data->b_in->echo_priority = 0;
	while (data->rl_decomp[row] && data->rl_decomp[row][j] != '\0')
	{
		if (data->rl_decomp[row][j] == '\"')
		{
			data->b_in->echo_dble_q++;
			if (data->b_in->echo_first == 0)
				data->b_in->echo_first = 2;
			if (data->b_in->echo_dble_q % 2 == 0 && data->b_in->echo_first == 2)
				data->b_in->echo_priority = 34;
		}
		else if (data->rl_decomp[row][j] == '\'')
		{
			data->b_in->echo_sgle_q++;
			if (data->b_in->echo_first == 0)
				data->b_in->echo_first = 1;
			if (data->b_in->echo_sgle_q % 2 == 0 && data->b_in->echo_first == 1)
				data->b_in->echo_priority = 39;
		}
		j++;
	}
	return ;
}

// void	clean_quote(t_vault *data, int row)
// {
// 	int		j;
// 	int		k;
// 	int		len;
// 	char	*temp;

// 	j = 0;
// 	k = 0;
// 	len = ft_strlen(data->rl_decomp[row]);
// 	temp = ft_calloc(len, sizeof(char));
// 	while (j < len)
// 	{
// 		if (data->rl_decomp[row][j] == data->b_in->echo_priority)
// 			j++;
// 		temp[k] = data->rl_decomp[row][j];
// 		j++;
// 		k++;
// 	}
// 	free (data->rl_decomp[row]);
// 	data->rl_decomp[row] = temp;
// }

// int	insert_row(int pos, int count, char **dest, char **source)
// {
// 	int	m;

// 	m = 0;
// 	while (m < count && source[m])
// 	{
// 		dest[pos] = ft_strdup(source[m]);
// 		free (source[m]);
// 		pos++;
// 		m++;
// 	}
// 	free (source);
// 	return (pos);
// }
