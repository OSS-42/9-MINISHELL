/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 14:05:06 by ewurstei          #+#    #+#             */
/*   Updated: 2022/12/28 10:21:03 by ewurstei         ###   ########.fr       */
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
	while (data->rl_dec[++row])
	{
		i = 0;
		while (data->rl_dec[row][i])
		{
			if (data->rl_dec[row][i] == '\'' || data->rl_dec[row][i] == '\"')
			{
				data->quote->quote_priority = data->rl_dec[row][i];
				while (data->rl_dec[row]
					&& data->rl_dec[row][i] != data->quote->quote_priority)
					i++;
			}
			else if (data->rl_dec[row][i] == '|')
				len++;
			i++;
		}
	}
	if (len > 0)
		expand_tab(data, len);
}

void	expand_tab(t_vault *data, int len)
{
	int		i;
	int		row;

	row = 0;
	i = 0;
	data->temp = NULL;
	data->temp = ft_calloc(sizeof(char *),
			ft_dbl_ptr_len(data->rl_dec) + len * 2 + 1);
	while (data->rl_dec[row])
	{
		if (ft_strchr(data->rl_dec[row], '|') == 0)
		{
			data->temp[i] = ft_strdup(data->rl_dec[row]);
			free (data->rl_dec[row]);
			i++;
		}
		else
		{
			search_for_pipe(data, row, &i);
			free (data->rl_dec[row]);
		}
		row++;
	}
	free(data->rl_dec);
	data->rl_dec = ft_dbl_ptr_copy(data->temp);
}

// en erreur 28/12 :
// echo bonjour"| wc" | cat -e (n'affiche rien)...

void	search_for_pipe(t_vault *data, int row, int *i)
{
	int	j;
	int	k;

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
			k = -1;
			while (data->rl_dec[row][j] && data->rl_dec[row][j] != '|')
				data->temp[*i][++k] = data->rl_dec[row][j++];
			(*i)++;
			j--;
		}
	}
}
