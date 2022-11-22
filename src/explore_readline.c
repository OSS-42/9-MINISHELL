/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   explore_readline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:55:29 by momo              #+#    #+#             */
/*   Updated: 2022/11/22 16:24:50 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	explore_readline(t_vault	*data)
{
	data->readline_decomposer = ft_split(data->read_line, ' ');
	if (ft_strcmp("cd", data->readline_decomposer[0]) == 1)
		ft_cd(data);
	if (ft_strcmp("pwd", data->readline_decomposer[0]) == 1)
		ft_pwd(data);
	if (ft_strcmp("echo", data->readline_decomposer[0]) == 1)
		ft_echo(data);
}
