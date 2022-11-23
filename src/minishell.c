/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbertin <mbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:22:01 by ewurstei          #+#    #+#             */
/*   Updated: 2022/11/23 10:50:02 by mbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	t_vault	data;

	data.test = getenv("PATH");
	while (1)
	{
		data.read_line = readline("alive>");
		add_history(data.read_line);
		explore_readline(&data);
		free(data.read_line);
	}
	return (0);
}
