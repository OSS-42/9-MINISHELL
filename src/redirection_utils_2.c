/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbertin <mbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 11:52:27 by mbertin           #+#    #+#             */
/*   Updated: 2022/12/19 12:11:23 by mbertin          ###   ########.fr       */
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
