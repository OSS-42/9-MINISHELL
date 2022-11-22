/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 13:04:10 by ewurstei          #+#    #+#             */
/*   Updated: 2022/11/22 13:13:10 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_echo(t_vault *data)
{
	char	**echo_args;
	int		i;
	int		flag_n;

	i = 1;
	flag_n = 0;
	if (echo_args[1] == "-n")
	{
		i = 2;
		flag_n = 1;
	}
	echo_args = ft_split(data, " ");
	while (echo_args[i])
	{
		ft_putstr_fd(echo_args[i], 1);
		i++;
	}
	if (flag_n == 0)
		ft_putstr_fd("\n", 1);
	else
		return (0);
}