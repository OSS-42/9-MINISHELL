/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbertin <mbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:22:01 by ewurstei          #+#    #+#             */
/*   Updated: 2022/12/01 16:49:36 by mbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern char	**environ;

void	init_data(t_vault *data)
{
	data->env = environ;
	data->read_line = NULL;
	data->b_in = ft_calloc(sizeof(t_builtins), 1);
	if (!data->b_in)
		return ;
	data->quote_in = ft_calloc(sizeof(t_quote), 1);
	data->flag = ft_calloc(sizeof(t_flag), 1);
	data->dollar = 0;
	data->activate_var = 0;
	data->flag->output_count = 0;
	data->flag->input_count = 0;
	data->flag->pipe_count = 0;
	data->quote_in->spc_count = 1;
	return ;
}

//system(INTRO) pour l'image au lancement de Minishell
int	main(void)
{
	t_vault	data;

	init_data(&data);
	system(INTRO);
//	data.b_in = malloc(sizeof(t_builtins));
//	data.env = environ;
	while (1)
	{
		data.read_line = readline("\033[95malive>\033[0;39m");
		if (ft_strcmp(data.read_line, "") != 0)
		{
			add_history(data.read_line);
			explore_readline(&data);
			free(data.read_line);
		}
	}
	return (0);
}
