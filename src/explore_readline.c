/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   explore_readline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbertin <mbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:55:29 by momo              #+#    #+#             */
/*   Updated: 2022/11/23 11:35:42 by mbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	explore_readline(t_vault *data)
{
	int	i;

	i = 0;
	data->readline_decomposer = ft_split(data->read_line, ' ');
	while (data->readline_decomposer[i])
	{
		if (ft_str)
	}
	built_in(data);
}

void	built_in(t_vault *data)
{
	if (ft_strcmp("cd", data->readline_decomposer[0]) == 1)
		ft_cd(data);
	if (ft_strcmp("pwd", data->readline_decomposer[0]) == 1)
		ft_pwd(data);
	if (ft_strcmp("echo", data->readline_decomposer[0]) == 1)
		ft_echo(data);
}
