/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 12:13:30 by ewurstei          #+#    #+#             */
/*   Updated: 2023/01/15 13:57:00 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pid_status_execve(t_vault *data)
{
	char	*temp;

	temp = NULL;
	temp = ft_itoa(WEXITSTATUS(data->status));
	put_code_in_fd(temp, data->error_fd);
	ft_free_n_null(temp);
	temp = NULL;
	return ;
}

void	good_code_format(t_vault *data)
{
	char	*temp;
	int		val_temp;

	temp = NULL;
	val_temp = 0;
	val_temp = ft_atoi(data->cmd->opt[1]);
	temp = ft_itoa(val_temp);
	put_code_in_fd(temp, data->error_fd);
	ft_free_n_null(temp);
	temp = NULL;
}
