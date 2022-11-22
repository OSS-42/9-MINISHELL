/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:22:04 by ewurstei          #+#    #+#             */
/*   Updated: 2022/11/21 13:31:28 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	lexer(t_vault *data)
{
	long	i;

	i = 0;
	data->line_decomposer = ft_split(data->line, ' ');
	while (data->line_decomposer)
		i++;
	while (--i > 0)
	{
		if (data->line_decomposer[i])
			pour chaque ligne du tableau, check pour quotes ('', "")
				si double quote, re spliter.
				si single quote, ....(a definir)
			pour chaque ligne du tableau, check pour les redirections (>>, <, >, <<, $?)
				si redirection, mettre des flags a "ON" car elles seront faites plus tard dans le cas de multiples commandes (pipes)
			pour chaque ligne du table, check pour multiples commandes (|)
				si multiples commandes --> pipex
			pour chaque ligne du tableau, check pour commande built-in (voir liste)
				si built-in, rediriger vers fonction fabriquee par nous, sinon access + execve
	}
}