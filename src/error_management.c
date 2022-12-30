/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 22:20:15 by ewurstei          #+#    #+#             */
/*   Updated: 2022/12/30 11:00:26 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_error(t_vault *data, int line)
{
	if (!(data->cmd->opt[line])
		|| ft_str_env_var(data->cmd->opt[line], 0) == 0)
		return (0);
	return (1);
}

void	message(t_vault *data, char *str1)
{
	ft_putstr_fd("minishell: ", 2);
	if (data->cmd->name)
	{
		ft_putstr_fd(data->cmd->name, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(str1, 2);
	return ;
}

void	error_message(t_vault *data)
{
	if (g_error_code == 1)
		message(data, "path or env missing");
	if (g_error_code == 2)
		message(data, "EOF on readline");
	if (g_error_code == 3)
		message(data, "FD error");
	if (g_error_code == 4)
		message(data, "no such file or directory");
	if (g_error_code == 5)
		message(data, "I/O error (dup2)");
	if (g_error_code == 6)
		message(data, "heredoc: no such file or directory");
	if (g_error_code == 7)
		message(data, "heredoc: I/O error ");
	if (g_error_code == 8)
		message(data, "pipe creation error");
	if (g_error_code == 9)
		message(data, "pid creation error");
	if (g_error_code == 10)
		message(data, "missing or wrong arguments");
	if (g_error_code == 11)
		message(data, "command not found");
	if (g_error_code == 12)
		message(data, "unexpected error");
}

//error codes :
// 1 - no path or no env
// 2 - EOF on readline
// 3 - FD error
// 4 - No such file or directory
// 5 - I/O error (dup2)
// 6 - heredoc - No such file or directory
// 7 - heredoc - I/O error (dup2)
// 8 - Pipe creation error
// 9 - PID creation error
// 10 - Arguments error
// 11 - Command not found