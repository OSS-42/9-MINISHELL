/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   explore_readline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momo <momo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:55:29 by momo              #+#    #+#             */
/*   Updated: 2022/11/21 14:51:17 by momo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	explore_readline(t_data	*data)
{
	data->read_line = readline("alive>");
	add_history(data->read_line);
	data->split_readline = ft_split(data->read_line, ' ');
	if (ft_strnstr(data->split_readline[0], "cd", 2) != NULL)
		ft_cd(data);
	// if (ft_strncmp(data->split_readline[0], "pwd", 3) == 0)
	// 	if (getcwd())
}

