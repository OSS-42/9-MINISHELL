/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbertin <mbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:22:01 by ewurstei          #+#    #+#             */
/*   Updated: 2022/12/14 14:17:32 by mbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern char	**environ;

void	init_data(t_vault *data)
{
	data->env = environ;
	data->read_line = NULL;
	data->b_in = ft_calloc(sizeof(t_builtins), 1);
	data->quote = ft_calloc(sizeof(t_quote), 1);
	data->flag = ft_calloc(sizeof(t_flag), 1);
	data->activate_var = 0;
	data->dollar_var = NULL;
	data->dollar_var_len = 0;
	data->rl_decomp = NULL;
	return ;
}

void	reinit_data(t_vault *data)
{
	data->flag->output_count = 0;
	data->flag->input_count = 0;
	data->flag->pipe_count = 0;
	data->quote->double_quote_count = 0;
	data->quote->simple_quote_count = 0;
	data->quote->begin = 0;
}

void	sig_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	return ;
}

//system(INTRO) pour l'image au lancement de Minishell
int	main(void)
{
	t_vault	data;

	signal(SIGINT, sig_handler);
	init_data(&data);
	system(INTRO);
	while (1)
	{
		data.read_line = readline("\033[95malive>\033[0;39m");
		// data.read_line[ft_strlen(data.read_line)] = '\0';
		if (data.read_line != NULL)
		{
			if (ft_strcmp(data.read_line, "") != 0)
			{
				add_history(data.read_line);
				explore_readline(&data);
				free(data.read_line);
				reinit_data(&data);
				free_dbl_ptr((void **)data.rl_decomp);
				// rajouter une fonction pour reinitialise certaine variable à 0 comme les compteurs de flags par exemple.
			}
		}
		else
		{
			printf("exit\n");
			ft_exit(&data);
		}
	}
	return (0);
}

// valgrind --leak-check=full  --show-reachable=yes --suppressions=./minishell.sup ./minishell