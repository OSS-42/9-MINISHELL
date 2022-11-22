/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   explore_readline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbertin <mbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:55:29 by momo              #+#    #+#             */
/*   Updated: 2022/11/22 09:37:45 by mbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	explore_readline(t_vault	*data)
{
	data->readline_decomposer = ft_split(data->read_line, ' ');
	if (ft_strcmp("cd", data->readline_decomposer[0]) == 1)
		ft_cd(data);
	// if (ft_strncmp(data->readline_decomposer[0], "pwd", 3) == 0)
	// 	if (getcwd())
}
