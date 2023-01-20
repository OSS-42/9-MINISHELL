/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:22:01 by ewurstei          #+#    #+#             */
/*   Updated: 2023/01/20 12:29:01 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_error_code = 0;

void	launch_minishell(t_vault *data)
{
	while (1)
	{
		init_signal(ALIVE);
		data->read_line = readline("alive>");
		if (data->read_line != NULL)
		{
			init_signal(EXEC);
			if (ft_strcmp(data->read_line, "") != 0)
				readline_exec(data);
		}
		else
		{
			data->flag->rl_exit = 1;
			close (data->flag->stdout_backup);
			close (data->flag->stdin_backup);
			error_message(data, "exit", "131\0");
			ft_exit(data);
		}
	}
	return ;
}

void	readline_exec(t_vault *data)
{
	add_history(data->read_line);
	explore_readline(data);
	ft_free_n_null(data->read_line);
	data->read_line = NULL;
	reinit_data(data);
}

int	main(int argc, char **argv, char **env)
{
	t_vault	data;

	(void) argc;
	(void) argv;
	init_data(&data, env);
	if (getenv("PATH") == NULL || data.env == NULL)
	{
		error_message(&data, "missing env or path", "1\0");
		ft_exit(&data);
	}
	intro_minishell();
	launch_minishell(&data);
	return (g_error_code);
}

void	readline_error(t_vault *data, int i)
{
	ft_dbl_ptr_free((void **)data->rl_dec);
	while (data->read_line[i] == ' ')
		i++;
	if (data->read_line[i] && data->read_line[i] != ' ')
		error_message(data, "missing or wrong arguments", "1\0");
}

// valgrind --leak-check=full  --show-reachable=yes --track-fds=yes
// --suppressions=./minishell.sup ./minishell