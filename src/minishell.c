/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:22:01 by ewurstei          #+#    #+#             */
/*   Updated: 2022/12/28 17:17:25 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern char	**environ;

void	init_data(t_vault *data)
{
	data->env = environ;
	data->read_line = NULL;
	data->tab_arg = NULL;
	data->b_in = ft_calloc(sizeof(t_builtins), 1);
	data->quote = ft_calloc(sizeof(t_quote), 1);
	data->flag = ft_calloc(sizeof(t_flag), 1);
	data->cmd = ft_calloc(sizeof(t_cmd), 1);
	data->dollar_var = NULL;
	data->dollar_var_len = 0;
	data->rl_dec = NULL;
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

int	main(void)
{
	t_vault	data;

	intro_minishell();
	signal(SIGINT, sig_handler);
	init_data(&data);
	while (1)
	{
		data.read_line = readline("\033[95malive>\033[0;39m");
		if (data.read_line != NULL)
		{
			if (ft_strcmp(data.read_line, "") != 0)
				readline_exec(&data);
		}
		else
		{
			printf("exit\n");
			close (data.flag->stdout_backup);
			close (data.flag->stdin_backup);
			ft_exit(&data, 1);
		}
	}
	return (0);
}
// sigaction, sigemptyset, sigaddset
// valgrind --leak-check=full  --show-reachable=yes --suppressions=./minishell.sup ./minishell