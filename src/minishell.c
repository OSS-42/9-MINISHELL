/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbertin <mbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:22:01 by ewurstei          #+#    #+#             */
/*   Updated: 2022/11/28 10:24:02 by mbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

extern char	**environ;

int	main(void)
{
	t_vault	data;

	system(INTRO);
	data.env = environ;
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
