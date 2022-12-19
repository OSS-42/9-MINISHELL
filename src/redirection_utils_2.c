/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbertin <mbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 11:52:27 by mbertin           #+#    #+#             */
/*   Updated: 2022/12/19 11:52:54 by mbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	dup_from_begin(t_vault *data, int decomp_i, int j, char *temp)
{
	while (data->rl_decomp[decomp_i][data->begin]
		&& data->rl_decomp[decomp_i][data->begin] != '\0')
	{
		temp[j] = data->rl_decomp[decomp_i][data->begin];
		data->begin++;
		j++;
	}
	data->begin = 0;
	free (data->rl_decomp[decomp_i]);
	data->rl_decomp[decomp_i] = temp;
}

int	while_not_chevron(t_vault *data, int i, char *str, int *begin)
{
	int	temp;

	temp = 0;
	while (data->rl_decomp[i][*begin] != data->flag->chevron)
	{
		str[temp] = data->rl_decomp[i][*begin];
		temp++;
		(*begin)++;
	}
	str[temp] = data->rl_decomp[i][*begin];
	temp++;
	(*begin)++;
	return (temp);
}
