/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   explore_readline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:55:29 by momo              #+#    #+#             */
/*   Updated: 2022/12/09 00:15:52 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	explore_readline(t_vault *data)
{
	// count_meta_with_space(data);
	data->rl_decomp = ft_split(data->read_line, ' ');
	if (rl_prio_n_qty(data) == TRUE)
	{
		data->rl_decomp_i = 0;
		find_str_quote(data);
		flag_count(data);
		execute_redirection(data);
//		spe_char(data, 0);
		built_in(data);
		dup2(data->flag->stdout_backup, STDOUT_FILENO);
	}
	return ;
}

void	built_in(t_vault *data)
{
	int	i;

	i = 1;
	if (ft_strcmp("cd", data->rl_decomp[0]) == 0)
		ft_cd(data, i);
	if (ft_strcmp("pwd", data->rl_decomp[0]) == 0)
		ft_pwd(data, i);
	if (ft_strcmp("echo", data->rl_decomp[0]) == 0)
		ft_echo(data, i);
	if (ft_strcmp("env", data->rl_decomp[0]) == 0)
		ft_env (data, 1);
	if (ft_strcmp("export", data->rl_decomp[0]) == 0)
		ft_export (data, i);
	if (ft_strcmp("unset", data->rl_decomp[0]) == 0)
		ft_unset (data, i);
	if (ft_strcmp("exit", data->rl_decomp[0]) == 0)
		ft_exit (data);
	return ;
}
