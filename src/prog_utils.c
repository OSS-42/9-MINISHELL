/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prog_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbertin <mbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 10:27:46 by ewurstei          #+#    #+#             */
/*   Updated: 2023/01/02 11:10:01 by mbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// penser aux retour de code d'erreur;
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
		ft_putstr_fd("1\0", data->error_fd);
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
		data->cmd->name = ft_strjoin(data->cmd->path, data->cmd->opt[0]);
		if (access(data->cmd->name, F_OK | X_OK) == 0)
		{
			ft_dbl_ptr_free((void **) data->path_names);
			execve(data->cmd->name, data->cmd->opt, data->env);
		}
		else
		{
			free(data->cmd->name);
			free(data->cmd->path);
		}
		i++;
	}
	data->cmd->name = ft_strdup(data->cmd->opt[0]);
}

void	find_prog(t_vault *data, int line)
{
	if (is_built_in(data->cmd->name) == 1)
	{
//		ft_dbl_ptr_free((void **) data->path_names);
		built_in(data, line);
		return ;
	}
	else if (access(data->cmd->name, F_OK | X_OK) == 0)
	{
		ft_dbl_ptr_free((void **) data->path_names);
		ft_putstr_fd("0\0", data->error_fd);
		execve(data->cmd->name, data->cmd->opt, data->env);
	}
	else if (access(data->cmd->name, F_OK | X_OK) != 0)
		cmd_path_check(data);
	ft_putstr_fd("127\0", data->error_fd);
	error_message(data, "command not found");
}
