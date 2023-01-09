/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 11:52:27 by mbertin           #+#    #+#             */
/*   Updated: 2023/01/09 17:01:15 by ewurstei         ###   ########.fr       */
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

int	return_len(t_vault *data, int i, int *temp, int len)
{
	(*temp)++;
	len++;
	while (data->tab_arg[i][*temp] == ' ')
		(*temp)++;
	if (data->tab_arg[i][*temp] == '\'' || data->tab_arg[i][*temp] == '\"')
	{
		data->quote->quote_priority = data->tab_arg[i][*temp];
		(*temp)++;
		while (data->tab_arg[i][*temp] != data->quote->quote_priority)
			(*temp)++;
		(*temp)++;
	}
	else
	{
		*temp = while_is_not_flag(data->tab_arg[i], *temp);
		len++;
	}
	while (data->tab_arg[i][*temp])
	{
		(*temp)++;
		len++;
	}
	return (len);
}
