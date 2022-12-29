/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:22:01 by ewurstei          #+#    #+#             */
/*   Updated: 2022/12/29 12:03:31 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern char	**environ;

void	init_data(t_vault *data)
{
	data->env = environ;
	data->exit_code = 0;
	find_paths(data);
	data->read_line = NULL;
	data->tab_arg = NULL;
	data->b_in = ft_calloc(sizeof(t_builtins), 1);
	data->quote = ft_calloc(sizeof(t_quote), 1);
	data->flag = ft_calloc(sizeof(t_flag), 1);
	data->cmd = ft_calloc(sizeof(t_cmd), 1);
	data->dollar_var = NULL;
	data->dollar_var_len = 0;
	data->rl_dec = NULL;
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
			ft_exit(data, 1);
		}
	}
	return ;
}

int	main(void)
{
	t_vault	data;

	init_data(&data);
	if (data.exit_code == 1)
	{
		message(&data, "unexpected error: ", "env or path missing", 67);
		return (0);
	}
	else
	{
		intro_minishell();
		launch_minishell(&data);
	}
	return (0);
}
// valgrind --leak-check=full  --show-reachable=yes --suppressions=./minishell.sup ./minishell