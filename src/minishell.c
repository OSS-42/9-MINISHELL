/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:22:01 by ewurstei          #+#    #+#             */
/*   Updated: 2022/12/31 15:54:52 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int g_error_code = 0;

void	init_data(t_vault *data, char **env)
{
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
	find_paths(data);
	data->flag->stdout_backup = dup(STDOUT_FILENO);
	data->flag->stdin_backup = dup(STDIN_FILENO);
	return ;
}

void	reinit_data(t_vault *data)
{
	data->flag->pipe_count = 0;
	data->quote->double_quote_count = 0;
	data->quote->simple_quote_count = 0;
	data->quote->begin = 0;
	data->quote->last_replace = 0;
	data->cmd->name = NULL;
}

void	readline_exec(t_vault *data)
{
	add_history(data->read_line);
	explore_readline(data);
	free(data->read_line);
	reinit_data(data);
	ft_dbl_ptr_free((void **)data->rl_dec);
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
			if (ft_strcmp(data->read_line, "") != 0)
				readline_exec(data);
		}
		else
		{
			printf("exit\n");
			close (data->flag->stdout_backup);
			close (data->flag->stdin_backup);
			g_error_code = 131;
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
	if (g_error_code != 0)
		ft_exit(&data);
	else
	{
		intro_minishell();
		launch_minishell(&data);
	}
	return (g_error_code);
}
// valgrind --leak-check=full  --show-reachable=yes --suppressions=./minishell.sup ./minishell