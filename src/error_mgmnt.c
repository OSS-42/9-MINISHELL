/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_mgmnt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 22:20:15 by ewurstei          #+#    #+#             */
/*   Updated: 2022/12/26 23:29:30 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_error(t_vault *data, int line)
{
	if (!(data->cmd->opt[line])
		|| ft_str_env_var(data->cmd->opt[line], 0) == 0)
		return (0);
	return (1);
}

int	message(t_vault *data, char *str1, char *str2, int error_code)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str1, 2);
	ft_putendl_fd(str2, 2);
	if (error_code == 9)
		close_pipe(data);
	else if (error_code == 8)
		free_dbl_ptr((void **)data->cmd->opt);
	return (error_code);
}

void	exit_on_error(t_vault *data, int error_code)
{
	if (error_code == 7)
		free_dbl_ptr((void **)data->path_names);
	else
		ft_exit (data, error_code);
}
