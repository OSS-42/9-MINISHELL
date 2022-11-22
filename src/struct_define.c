/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_define.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbertin <mbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 12:19:32 by momo              #+#    #+#             */
/*   Updated: 2022/11/22 09:03:44 by mbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern char	**environ;

// void	malloc_struct(t_data **data, int argc, char **argv, char **env)
// {
// 	*data = malloc(sizeof (t_data));
// 	if (!*data)
// 	{
// 		free(data);
// 		exit(EXIT_FAILURE);
// 	}
// 	init_struct(*data, argc, argv, env);
// }

void	init_struct(t_data **data)
{
	(*data)->env = environ;
}
