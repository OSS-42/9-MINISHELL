/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 00:19:39 by ewurstei          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/01/12 16:21:44 by mbertin          ###   ########.fr       */
=======
/*   Updated: 2023/01/12 16:21:39 by ewurstei         ###   ########.fr       */
>>>>>>> 58e4856440d4b6441823ae11e0920271bc490403
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	clean_before_exit(t_vault *data)
{
	free_struct_b_in(data);
	if (data->quote)
		free(data->quote);
	ft_free_n_null(data->read_line);
	data->read_line = NULL;
	if (data->env && data->flag->execve == 0)
		ft_dbl_ptr_free((void **)data->env);
	if (data->flag->rl_exit == 0)
	{
		if (data->tab_arg)
			ft_dbl_ptr_free((void **)data->tab_arg);
		if (data->pid)
			free (data->pid);
	}
	close_fd(data);
	free_struct_flag(data);
}

void	free_struct_flag(t_vault *data)
{
	if (data->flag->execve == 0)
	{
		if (data->cmd->opt && data->flag->rl_exit == 0)
			ft_dbl_ptr_free((void **)data->cmd->opt);
		ft_free_n_null(data->cmd->name);
		data->cmd->name = NULL;
		free (data->cmd);
	}
	if (data->flag->pipe)
		ft_dbl_ptr_free((void **)data->flag->pipe);
	data->flag->pipe = NULL;
	if (data->flag)
		free(data->flag);
}

void	free_struct_b_in(t_vault *data)
{
	ft_free_n_null(data->b_in->export_var);
	data->b_in->export_var = NULL;
	if (data->b_in->env_ord)
		ft_dbl_ptr_free((void **)data->b_in->env_ord);
	if (data->b_in)
		free(data->b_in);
	return ;
}

void	close_fd(t_vault *data)
{
	if (data->flag->fd_out > 0)
		close (data->flag->fd_out);
	if (data->flag->fd > 0)
		close (data->flag->fd);
	if (data->flag->heredoc_fd > 0)
	{
		unlink("temp_heredoc");
		close(data->flag->heredoc_fd);
	}
	close (data->flag->stdin_backup);
	close (data->flag->stdout_backup);
	// close (data->error_fd);
	return ;
}
