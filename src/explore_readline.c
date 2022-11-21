/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   explore_readline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momo <momo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:55:29 by momo              #+#    #+#             */
/*   Updated: 2022/11/21 15:50:34 by momo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	explore_readline(t_data	*data)
{
	data->read_line = readline("alive>");
	add_history(data->read_line);
	data->split_readline = ft_split(data->read_line, ' ');
	if (ft_strncmp("cd", data->split_readline[0], ft_strlen(data->split_readline[0])) == 0)
		ft_cd(data);
	// if (ft_strncmp(data->split_readline[0], "pwd", 3) == 0)
	// 	if (getcwd())
}
