/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   explore_readline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:55:29 by momo              #+#    #+#             */
/*   Updated: 2022/11/25 09:17:59 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	explore_readline(t_vault *data)
{
	data->rl_decomp = ft_split(data->read_line, ' ');
	built_in(data);
}

void	built_in(t_vault *data)
{
	if (ft_strcmp("cd", data->rl_decomp[0]) == 0)
		ft_cd(data);
	if (ft_strcmp("pwd", data->rl_decomp[0]) == 0)
		ft_pwd(data);
	if (ft_strcmp("echo", data->rl_decomp[0]) == 0)
		ft_echo(data);
	if (ft_strcmp("env", data->rl_decomp[0]) == 0)
		ft_env (data, 1);
	if (ft_strcmp("export", data->rl_decomp[0]) == 0)
		ft_export (data);
	if (ft_strcmp("unset", data->rl_decomp[0]) == 0)
		ft_unset (data);
	if (ft_strcmp("exit", data->rl_decomp[0]) == 0)
		ft_exit (0);
}
