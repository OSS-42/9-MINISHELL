/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 22:20:15 by ewurstei          #+#    #+#             */
/*   Updated: 2023/01/15 13:19:54 by ewurstei         ###   ########.fr       */
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

void	error_message(t_vault *data, char *message, char *code)
{
	put_code_in_fd(code, data->error_fd);
	g_error_code = ft_atoi(code);
	if (data->flag->rl_exit == 0)
		ft_putstr_fd("minishell: ", 2);
	if (data->cmd->name)
	{
		ft_putstr_fd(data->cmd->name, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(message, 2);
	return ;
}

char	*find_error_code(t_vault *data)
{
	char	*temp;
	int		read_val;

	temp = ft_calloc(sizeof(char), 4);
	data->error_fd = open("/tmp/.tmp_error", O_RDONLY);
	read_val = read(data->error_fd, temp, 3);
	if (read_val < 0)
		perror("reading error");
	close(data->error_fd);
	return (temp);
}

void	exit_process(t_vault *data)
{
	clean_before_exit(data);
	data->temp_str = find_error_code(data);
	g_error_code = ft_atoi(data->temp_str);
	ft_free_n_null (data->temp_str);
	data->temp_str = NULL;
	exit(g_error_code);
}

void	put_code_in_fd(char *code, int fd)
{
	fd = open("/tmp/.tmp_error",
			O_CREAT | O_WRONLY | O_TRUNC, 0644);
	ft_putstr_fd(code, fd);
	close (fd);
}

//bash error codes :
// 1 - Catchall for general errors
// 2 - Misuse of shell builtins
// 126 - Command invoked cannot execute
// 127 - "command not found"
// 128 - Invalid argument to exit
// 128 + n - Fatal error signal "n"
// 130 - Script terminated by Control-C
// 255 - Exit status out of range (seulement int 0 - 255)

//custom error codes (not implemented):
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