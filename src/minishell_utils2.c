/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 12:13:30 by ewurstei          #+#    #+#             */
/*   Updated: 2023/01/19 20:02:12 by ewurstei         ###   ########.fr       */
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

char	*check_env_home_exist(t_vault *data)
{
	int		i;
	int		slen;
	char	*temp;

	i = 0;
	slen = 0;
	temp = NULL;
	while (data->env[i] && data->env[i][0])
	{
		if (ft_strnstr(data->env[i], "HOME=", 5) != NULL)
		{
			slen = ft_strlen(data->env[i]);
			temp = ft_substr(data->env[i], 5, slen);
			return (temp);
		}
		i++;
	}
	return (temp);
}
