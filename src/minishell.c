/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:22:01 by ewurstei          #+#    #+#             */
/*   Updated: 2022/12/06 21:13:48 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern char	**environ;

void	init_data(t_vault *data)
{
	data->env = environ;
	data->read_line = NULL;
	data->b_in = ft_calloc(sizeof(t_builtins), 1);
	data->quote_in = ft_calloc(sizeof(t_quote), 1);
	data->flag = ft_calloc(sizeof(t_flag), 1);
	data->activate_var = 0;
	data->flag->output_count = 0;
	data->flag->input_count = 0;
	data->flag->pipe_count = 0;
	data->dollar_var = NULL;
	data->dollar_var_len = 0;
	data->quote_in->double_quote_count = 0;
	data->quote_in->simple_quote_count = 0;
	data->flag->stdout_backup = 0;
	return ;
}

void	reinit_data(t_vault *data)
{
	data->flag->output_count = 0;
	data->flag->input_count = 0;
	data->flag->pipe_count = 0;
	data->flag->dollar_count = 0;
	data->quote_in->double_quote_count = 0;
	data->quote_in->simple_quote_count = 0;
}

//system(INTRO) pour l'image au lancement de Minishell
int	main(void)
{
	t_vault	data;

	init_data(&data);
	system(INTRO);
	while (1)
	{
		data.read_line = readline("\033[95malive>\033[0;39m");
		if (ft_strcmp(data.read_line, "") != 0)
		{
			add_history(data.read_line);
			explore_readline(&data);
			free(data.read_line);
			reinit_data(&data);
			// rajouter une fonction pour reinitialise certaine variable à 0 comme les compteurs de flags par exemple.
		}
	}
	return (0);
}

// valgrind --leak-check=full  --show-reachable=yes --suppressions=./minishell.sup ./minishell