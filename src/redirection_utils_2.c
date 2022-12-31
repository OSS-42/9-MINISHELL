/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momo <momo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 11:52:27 by mbertin           #+#    #+#             */
/*   Updated: 2022/12/31 16:30:43 by momo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	dup_from_begin(t_vault *data, int decomp_i, int j, char *temp)
{
	while (data->rl_dec[decomp_i][data->begin]
		&& data->rl_dec[decomp_i][data->begin] != '\0')
	{
		temp[j] = data->rl_dec[decomp_i][data->begin];
		data->begin++;
		j++;
	}
	data->begin = 0;
	free (data->rl_dec[decomp_i]);
	data->rl_dec[decomp_i] = temp;
}

int	is_in_quote(t_vault *data, int line, int array)
{
	int	i;

	i = 0;
	while (data->tab_arg[line][i])
	{
		if (data->tab_arg[line][i] == '\'' || data->tab_arg[line][i] == '\"')
		{
			data->quote->quote_priority = data->tab_arg[line][i];
			i++;
			while (data->tab_arg[line] && data->tab_arg[line][i]
				!= data->quote->quote_priority)
			{
				if (i == array)
					return (TRUE);
				i++;
			}
		}
		i++;
	}
	return (FALSE);
}
