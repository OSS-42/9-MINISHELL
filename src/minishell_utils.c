/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 23:09:55 by ewurstei          #+#    #+#             */
/*   Updated: 2023/01/11 15:08:48 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_row(t_vault *data, int line)
{
	if ((data->b_in->echo_flag_n == 1 && data->b_in->forget_minus == 0))
	{
		ft_putstr_fd(data->cmd->opt[line], 1);
		data->b_in->first_word = 0;
	}
	else if (data->b_in->first_word == 1)
	{
		ft_putstr_fd(data->cmd->opt[line], 1);
		data->b_in->first_word = 0;
	}
	else
	{
		ft_putstr_fd(" ", 1);
		ft_putstr_fd(data->cmd->opt[line], 1);
	}
	return ;
}

int	ft_isinset(char c)
{
	if (c == '\'')
		return (1);
	else if (c == '\"')
		return (2);
	else if (c == '$')
		return (3);
	else
		return (0);
}

void	export_only_format(t_vault *data, char *buff2, char **temp, int i)
{
	data->buffer = ft_strjoin("declare -x ", temp[i]);
	ft_free_n_null (temp[i]);
	temp[i] = ft_strdup(data->buffer);
	ft_free_n_null (data->buffer);
	data->buffer = ft_strjoin(temp[i], "\"");
	ft_free_n_null (temp[i]);
	temp[i] = ft_strdup(data->buffer);
	ft_free_n_null (data->buffer);
	buff2 = ft_strtrim(ft_strchr(data->env[i], '='), "=");
	data->buffer = ft_strjoin(temp[i], buff2);
	ft_free_n_null (buff2);
	buff2 = NULL;
	ft_free_n_null (temp[i]);
	temp[i] = ft_strdup(data->buffer);
	ft_free_n_null (data->buffer);
	data->buffer = ft_strjoin(temp[i], "\"");
	ft_free_n_null (temp[i]);
	temp[i] = ft_strdup(data->buffer);
	ft_free_n_null (data->buffer);
	data->buffer = NULL;
}

void	heredoc_unlink(t_vault *data)
{
	if (data->flag->heredoc == TRUE)
	{
		data->flag->heredoc = FALSE;
		unlink("temp_heredoc");
	}
}

void	execve_fail(t_vault *data)
{
	ft_putstr_fd("unexpected error\n", STDOUT_FILENO);
	data->error_fd = open("/tmp/.tmp_error", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	ft_putstr_fd("127\0", data->error_fd);
	close (data->error_fd);
	ft_free_n_null(data->cmd->name);
	ft_dbl_ptr_free((void **)data->cmd->opt);
	ft_dbl_ptr_free((void **)data->env);
	ft_free_n_null(data->cmd->path);
	data->cmd->path = NULL;
	free(data->cmd);
	exit (127);
}
