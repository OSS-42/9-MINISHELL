/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 14:05:06 by ewurstei          #+#    #+#             */
/*   Updated: 2023/01/11 12:06:26 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_for_pipe(t_vault *data)
{
	int		row;
	int		i;
	int		len;

	row = -1;
	len = 0;
	while (data->rl_dec[++row] && data->rl_dec[row][0])
	{
		i = -1;
		while (data->rl_dec[row][++i])
		{
			if (data->rl_dec[row][i] == '\'' || data->rl_dec[row][i] == '\"')
			{
				data->quote->quote_priority = data->rl_dec[row][i];
				i++;
				while (data->rl_dec[row]
					&& data->rl_dec[row][i] != data->quote->quote_priority)
					i++;
			}
			else if (data->rl_dec[row][i] == '|')
				len++;
		}
	}
	if (len > 0)
		expand_tab(data, len);
}

void	expand_tab(t_vault *data, int len)
{
	int		i;
	int		row;

	row = -1;
	i = 0;
	data->temp = NULL;
	data->temp = ft_calloc(sizeof(char *),
			ft_dbl_ptr_len(data->rl_dec) + len * 2 + 1);
	while (data->rl_dec[++row])
	{
		if (ft_strchr(data->rl_dec[row], '|') == 0)
		{
			data->temp[i] = ft_strdup(data->rl_dec[row]);
			ft_free_n_null (data->rl_dec[row]);
			data->rl_dec[row] = NULL;
			i++;
		}
		else
		{
			search_for_pipe(data, row, &i);
			ft_free_n_null (data->rl_dec[row]);
			data->rl_dec[row] = NULL;
		}
	}
	free(data->rl_dec);
	data->rl_dec = ft_dbl_ptr_copy(data->temp);
	ft_dbl_ptr_free((void **)data->temp);
}

void	search_for_pipe(t_vault *data, int row, int *i)
{
	int	j;

	j = -1;
	while (data->rl_dec[row][++j])
	{
		if (data->rl_dec[row][j] == '|')
		{
			data->temp[*i] = ft_calloc(sizeof(char), 2);
			data->temp[*i][0] = '|';
			(*i)++;
		}
		else
		{
			data->temp[*i] = ft_calloc(sizeof(char),
					ft_strlen(data->rl_dec[row]));
			j = prep_temp(data, row, i, j);
			(*i)++;
			j--;
		}
	}
}

int	prep_temp(t_vault *data, int row, int *i, int j)
{
	int	k;

	k = 0;
	while (data->rl_dec[row][j] && data->rl_dec[row][j] != '|')
	{
		if (data->rl_dec[row][j] == '\'' || data->rl_dec[row][j] == '\"')
		{
			data->quote->quote_priority = data->rl_dec[row][j];
			data->temp[*i][k++] = data->rl_dec[row][j++];
			while (data->rl_dec[row][j] != data->quote->quote_priority)
				data->temp[*i][k++] = data->rl_dec[row][j++];
			data->temp[*i][k++] = data->rl_dec[row][j++];
		}
		else
			data->temp[*i][k++] = data->rl_dec[row][j++];
	}
	return (j);
}

//l:91
// k = 0;
// while (data->rl_dec[row][j] && data->rl_dec[row][j] != '|')
// {
// 	if (data->rl_dec[row][j] == '\'' || data->rl_dec[row][j] == '\"')
// 	{
// 		data->quote->quote_priority = data->rl_dec[row][j];
// 		data->temp[*i][k++] = data->rl_dec[row][j++];
// 		while (data->rl_dec[row][j] != data->quote->quote_priority)
// 			data->temp[*i][k++] = data->rl_dec[row][j++];
// 		data->temp[*i][k++] = data->rl_dec[row][j++];
// 	}
// 	else
// 		data->temp[*i][k++] = data->rl_dec[row][j++];
// }