/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momo <momo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 15:24:04 by mbertin           #+#    #+#             */
/*   Updated: 2023/01/19 12:01:39 by momo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	heredoc(t_vault *data, int line)
{
	char	*str;

	if (data->flag->heredoc_fd > 0)
		close (data->flag->heredoc_fd);
	dup2(data->flag->stdin_backup, STDIN_FILENO);
	dup2(data->flag->stdout_backup, STDOUT_FILENO);
	data->flag->heredoc_fd = open("temp_heredoc", O_CREAT
			| O_WRONLY | O_TRUNC, 0644);
	while (data->flag->heredoc_delimiter == FALSE)
	{
		str = readline("HEREDOC> ");
		if (str == NULL)
		{
			free(str);
			break ;
		}
		check_eof(data, str);
	}
	reset_n_close_heredoc(data);
	if (data->flag->pipe_count > 0
		&& (line == 0 || line != ft_dbl_ptr_len(data->tab_arg) - 1))
		dup2(data->flag->pipe[line][p_write], STDOUT_FILENO);
	if (data->flag->fd_out > 0)
		dup2(data->flag->fd_out, STDOUT_FILENO);
}

void	check_eof(t_vault *data, char *str)
{
	if (ft_strncmp(str, data->flag->output,
			ft_strlen(data->flag->output)) == 0
		&& ft_strlen(str) == ft_strlen(data->flag->output))
		data->flag->heredoc_delimiter = TRUE;
	else
	{
		ft_putstr_fd(str, data->flag->heredoc_fd);
		ft_putstr_fd("\n", data->flag->heredoc_fd);
	}
	free(str);
}

void	reset_n_close_heredoc(t_vault *data)
{
	data->flag->heredoc_delimiter = FALSE;
	data->flag->heredoc = TRUE;
	close(data->flag->heredoc_fd);
	return ;
}
