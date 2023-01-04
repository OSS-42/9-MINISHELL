/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momo <momo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 15:24:04 by mbertin           #+#    #+#             */
/*   Updated: 2023/01/03 20:33:32 by momo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	heredoc(t_vault *data)
{
	char	*str;

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
	data->flag->heredoc_delimiter = FALSE;
	data->flag->heredoc = TRUE;
	ft_putstr_fd("\n", data->flag->heredoc_fd);
	close(data->flag->heredoc_fd);
	if (data->flag->fd_out > 0)
		dup2(data->flag->fd_out, STDOUT_FILENO);
// Ajouter un dup2 pour le pipe sur std_out si la fonction est compris entre deux pipes
}
