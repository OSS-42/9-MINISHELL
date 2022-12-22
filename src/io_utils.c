/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 11:38:02 by ewurstei          #+#    #+#             */
/*   Updated: 2022/12/22 11:49:07 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	io_redirection(t_vault *data, int input, int output)
{
	if (dup2(input, STDIN_FILENO) == -1)
		exit_on_error(data, 1);
	if (dup2(output, STDOUT_FILENO) == -1)
		exit_on_error(data, 1);
}

int	dup_fds(t_vault *data, int line)
{
	int	len;

	len = ft_dbl_ptr_len(data->tab_arg);
	if (line == 0)
	{
		if (dup2(data->flag->pipe[line][p_write], STDOUT_FILENO) == -1)
			exit_on_error(data, 1);
	}
	else if (line != len - 1)
		io_redirection(data, data->flag->pipe[line - 1][p_read],
			data->flag->pipe[line][p_write]);
	else
	{
		if (dup2(data->flag->pipe[line - 1][p_read], STDIN_FILENO) == -1)
			exit_on_error(data, 1);
	}
	return (0);
}

void	close_pipe(t_vault *data)
{
	int	x;

	x = 0;
	while (x < data->flag->pipe_count)
	{
		close (data->flag->pipe[x][p_write]);
		close (data->flag->pipe[x][p_read]);
		free (data->flag->pipe[x]);
		x++;
	}
	free(data->flag->pipe);
	return ;
}

void	reset_io(t_vault *data)
{
	dup2(data->flag->stdout_backup, STDOUT_FILENO);
	dup2(data->flag->stdin_backup, STDIN_FILENO);
	close (data->flag->stdout_backup);
	close (data->flag->stdin_backup);
}
