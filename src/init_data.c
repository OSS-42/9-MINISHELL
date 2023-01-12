/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 15:24:14 by mbertin           #+#    #+#             */
/*   Updated: 2023/01/12 16:59:04 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_data(t_vault *data, char **env)
{
	put_code_in_fd("0\0", data->error_fd);
	data->env = ft_dbl_ptr_copy(env);
	data->buffer = NULL;
	data->cmd = ft_calloc(sizeof(t_cmd), 1);
	data->b_in = ft_calloc(sizeof(t_builtins), 1);
	data->quote = ft_calloc(sizeof(t_quote), 1);
	data->flag = ft_calloc(sizeof(t_flag), 1);
	data->rl_dec = NULL;
	data->dollar_var = NULL;
	data->read_line = NULL;
	data->tab_arg = NULL;
	data->dollar_var_len = 0;
	data->path_names = NULL;
	data->flag->stdout_backup = dup(STDOUT_FILENO);
	data->flag->stdin_backup = dup(STDIN_FILENO);
	data->fail_redir = FALSE;
	data->flag->execve = 0;
	data->flag->rl_exit = 0;
	data->pid = NULL;
	return ;
}

void	reinit_data(t_vault *data)
{
	data->flag->pipe_count = 0;
	data->quote->double_quote_count = 0;
	data->quote->simple_quote_count = 0;
	data->quote->begin = 0;
	data->quote->last_replace = 0;
	data->flag->var_not_found = 0;
	data->fail_redir = FALSE;
	ft_free_n_null (data->cmd->name);
	data->cmd->name = NULL;
	if (data->cmd->opt)
		ft_dbl_ptr_free((void **)data->cmd->opt);
	data->cmd->opt = NULL;
	if (data->tab_arg)
		ft_dbl_ptr_free((void **)data->tab_arg);
	data->tab_arg = NULL;
}

void	reinit_fd(t_vault *data)
{
	if (data->flag->fd_out > 0)
		close (data->flag->fd_out);
	data->flag->fd_out = 0;
	if (data->flag->fd > 0)
		close (data->flag->fd);
	data->flag->fd = 0;
	if (data->flag->heredoc_fd > 0)
	{
		unlink("temp_heredoc");
		close (data->flag->heredoc_fd);
	}
	data->flag->heredoc_fd = 0;
}
