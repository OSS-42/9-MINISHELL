/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_mgmnt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 22:20:15 by ewurstei          #+#    #+#             */
/*   Updated: 2022/12/01 23:08:24 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_error(t_vault *data, int row)
{
	if (!(data->rl_decomp[row]) || ft_str_env_var(data->rl_decomp[row], 0) == 0)
		return (0);
	return (1);
}
