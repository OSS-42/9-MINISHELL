/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prog_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 10:27:46 by ewurstei          #+#    #+#             */
/*   Updated: 2022/12/22 10:43:58 by ewurstei         ###   ########.fr       */
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
		printf("error 65");
//		exit_on_error(data, message(data, "Unexpected error.", "", 7));
	else
	{
		data->path_names = ft_split(data->paths, ':');
		free (data->paths);
	}
}

void	cmd_path_check(t_vault *data)
{
	size_t	x;

	x = 0;
	while (data->path_names[x])
	{
		data->cmd->path = ft_strjoin(data->path_names[x], "/");
		data->cmd->name = ft_strjoin(data->cmd->path, data->cmd->options[0]);
		if (access(data->cmd->name, F_OK | X_OK) == 0)
			execve(data->cmd->name, data->cmd->options, data->env);
		else
		{
			free(data->cmd->name);
			free(data->cmd->path);
		}
		x++;
	}
}

void	find_prog(t_vault *data, int line)
{
	data->cmd->options = ft_split(data->tab_arg[line], ' ');
	if (!data->cmd->options)
		printf("error 66");
//		exit_on_error(data, message(data, "Unexpected error.", "", 0));
	if (access(data->cmd->options[0], F_OK | X_OK) == 0)
	{
		data->cmd->name = data->cmd->options[0];
		execve(data->cmd->name, data->cmd->options, data->env);
	}
	else if (access(data->cmd->options[0], F_OK | X_OK) != 0)
		cmd_path_check(data);
	printf("error 67");
//	exit_on_error(data, message(data, "Command not found: ",
//			data->cmd.options[0], 8));
}
