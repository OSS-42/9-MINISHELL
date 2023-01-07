/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momo <momo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:22:01 by ewurstei          #+#    #+#             */
/*   Updated: 2023/01/07 18:03:11 by momo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_error_code = 0;

void	init_data(t_vault *data, char **env)
{
	data->error_fd = open(".tmp_error", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	ft_putstr_fd("0\0", data->error_fd);
	close(data->error_fd);
	data->env = env;
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
	data->flag->stdout_backup = dup(STDOUT_FILENO);
	data->flag->stdin_backup = dup(STDIN_FILENO);
	data->fail_redir = FALSE;
	data->flag->execve = 0;
	data->flag->rl_exit = 0;
	data->pid = NULL;
	if (getenv("PATH") == NULL)
	{
		error_message(data, "missing env or path", "1\0");
		ft_exit(data);
	}
	return ;
}

void	reinit_data(t_vault *data)
{
	data->flag->pipe_count = 0;
	if (data->flag->fd_out > 0)
		close (data->flag->fd_out);
	if (data->flag->fd > 0)
		close (data->flag->fd);
	if (data->flag->heredoc_fd > 0)
		close (data->flag->heredoc_fd);
	data->flag->heredoc_fd = 0;
	data->flag->fd_out = 0;
	data->flag->fd = 0;
	data->quote->double_quote_count = 0;
	data->quote->simple_quote_count = 0;
	data->quote->begin = 0;
	data->quote->last_replace = 0;
	data->fail_redir = FALSE;
	free (data->cmd->name);
	data->cmd->name = NULL;
	if (data->cmd->opt)
		ft_dbl_ptr_free((void **)data->cmd->opt);
	ft_dbl_ptr_free((void **)data->tab_arg);
}

void	readline_exec(t_vault *data)
{
	add_history(data->read_line);
	explore_readline(data);
	free(data->read_line);
	reinit_data(data);
}

void	launch_minishell(t_vault *data)
{
	while (1)
	{
		init_signal(ALIVE);
		data->read_line = readline("\033[95malive>\033[0;39m");
		if (data->read_line != NULL)
		{
			init_signal(EXEC);
			// data->error_fd = open(".tmp_error", O_CREAT | O_WRONLY | O_TRUNC, 0644);
			// ft_putstr_fd("0\0", data->error_fd); // ou l'ouvre deja dans data ...
			if (ft_strcmp(data->read_line, "") != 0)
				readline_exec(data);
		}
		else
		{
			// printf("exit\n");
			// close (data->error_fd); // rajout ici pour ne pas ecrase si deja ouvert
			// data->error_fd = open(".tmp_error", O_CREAT | O_WRONLY
			// 		| O_TRUNC, 0644);
			// ft_putstr_fd("131\0", data->error_fd);
			// close (data->error_fd); // voir si ca pose pas de probleme avec eric
			data->flag->rl_exit = 1;
			close (data->flag->stdout_backup);
			close (data->flag->stdin_backup);
			error_message(data, "exit", "131\0");
			ft_exit(data);
		}
	}
	return ;
}

int	main(int argc, char **argv, char **env)
{
	t_vault	data;

	(void) argc;
	(void) argv;
	init_data(&data, env);
	// data.temp_str = find_error_code(&data);
	// g_error_code = ft_atoi(data.temp_str);
	// free (data.temp_str);
	// if (g_error_code != 0)
	// {
	// 	error_message(&data, "missing env or path", "1\0");
	// 	ft_exit(&data);
	// }
	// else
	// {
		intro_minishell();
		launch_minishell(&data);
	// }
	return (g_error_code);
}
// valgrind --leak-check=full  --show-reachable=yes --track-fds=yes
// --suppressions=./minishell.sup ./minishell