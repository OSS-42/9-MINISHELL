/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_define.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momo <momo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 12:19:32 by momo              #+#    #+#             */
/*   Updated: 2022/11/21 13:59:37 by momo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	malloc_struct(t_data **data, int argc, char **argv, char **env)
{
	*data = malloc(sizeof (t_data));
	if (!*data)
	{
		free(data);
		exit(EXIT_FAILURE);
	}
	init_struct(*data, argc, argv, env);
}


void	init_struct(t_data *data, int argc, char **argv, char **env)
{
	data->argc = argc;
	data->argv = argv;
	data->env = env;
}