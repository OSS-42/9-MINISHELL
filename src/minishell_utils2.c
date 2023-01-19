/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momo <momo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 12:13:30 by ewurstei          #+#    #+#             */
/*   Updated: 2023/01/19 11:12:03 by momo             ###   ########.fr       */
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

int	check_wrong_redirection(t_vault *data)
{
	if (pipe_after_chevron(data, 0) == FALSE)
		return (FALSE);
	if (opposite_chevron(data, 0) == FALSE)
		return (FALSE);
	if (triple_chevron(data, 0) == FALSE)
		return (FALSE);
	if (chevron_space_chevron(data, 0) == FALSE)
		return (FALSE);
	return (TRUE);
}
