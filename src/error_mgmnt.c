/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_mgmnt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 22:20:15 by ewurstei          #+#    #+#             */
/*   Updated: 2022/12/29 17:42:09 by ewurstei         ###   ########.fr       */
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

int	message(t_vault *data, char *str1, int error_code)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(data->cmd->name, 2);
	ft_putendl_fd(str1, 2);
	return (error_code);
}

void	free_all(t_vault *data)
{
	if (data->b_in->export_var)
		free (data->b_in->export_var);
	if (data->b_in->env_export)
		ft_dbl_ptr_free((void **)data->b_in->env_export);
	if (data->b_in->env_unset)
		ft_dbl_ptr_free((void **)data->b_in->env_unset);
	if (data->b_in->env_ord)
		free(data->b_in->env_ord);
	if (data->read_line)
		free(data->read_line);
	if (data->b_in)
		free(data->b_in);
	if (data->quote)
		free(data->quote);
	if (data->flag)
		free(data->flag);
	if (data->tab_arg)
		ft_dbl_ptr_free((void **)data->tab_arg);
	exit (g_error_code);
}
	//ne pas oublier exit_minishell();

//error codes :
// 1 - no path or no env
// 2 - EOF on readline
// 3 - FD error
// 4 - No such file or directory
// 5 - I/O error (dup2)
// 6 - heredoc - No such file or directory
// 7 - heredoc - I/O error (dup2)
// 8 - Pipe creation error
// 9 - PID creation error
// 10 - Arguments error
// 11 - Command not found