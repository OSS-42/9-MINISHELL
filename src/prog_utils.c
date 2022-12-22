/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prog_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbertin <mbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 10:27:46 by ewurstei          #+#    #+#             */
/*   Updated: 2022/12/22 15:46:11 by mbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	find_paths(t_vault *data)
{
	size_t	i;
	size_t	slen;

	i = 0;
	data->paths = NULL;
	while (data->env[i] && data->env[i][0])
	{
		if (ft_strnstr(data->env[i], "PATH=", 5) != NULL)
		{
			slen = ft_strlen(data->env[i]);
			data->paths = ft_substr(data->env[i], 5, slen);
			break ;
		}
		i++;
	}
	if (!data->paths || !data->env[i])
		exit_on_error(data, message(data, "Unexpected error.", "", 7));
	else
	{
		data->path_names = ft_split(data->paths, ':');
		free (data->paths);
	}
}

void	cmd_path_check(t_vault *data)
{
	size_t	i;

	i = 0;
	while (data->path_names[i])
	{
		data->cmd->path = ft_strjoin(data->path_names[i], "/");
		data->cmd->name = ft_strjoin(data->cmd->path, data->cmd->options[0]);
		if (access(data->cmd->name, F_OK | X_OK) == 0)
			execve(data->cmd->name, data->cmd->options, data->env);
		else
		{
			free(data->cmd->name);
			free(data->cmd->path);
		}
		i++;
	}
}

void	find_prog(t_vault *data)
{
	if (is_built_in(data->cmd->name) == 1)
	{
		built_in(data);
		return ;
	}
	else if (access(data->cmd->name, F_OK | X_OK) == 0)
		execve(data->cmd->name, data->cmd->options, data->env);
	else if (access(data->cmd->name, F_OK | X_OK) != 0)
		cmd_path_check(data);
	exit_on_error(data, message(data, "Command not found: ",
			data->cmd->options[0], 8));
}
