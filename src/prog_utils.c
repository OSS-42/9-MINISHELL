/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prog_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbertin <mbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 10:27:46 by ewurstei          #+#    #+#             */
/*   Updated: 2023/01/10 13:20:11 by mbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	find_paths(t_vault *data)
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
		return (FALSE);
	else
	{
		data->path_names = ft_split(data->paths, ':');
		free (data->paths);
	}
	return (TRUE);
}

void	cmd_path_check(t_vault *data)
{
	size_t	i;

	i = -1;
	if (find_paths(data) == FALSE)
		return ;
	while (data->path_names[++i])
	{
		data->cmd->path = ft_strjoin(data->path_names[i], "/");
		if (i == 0)
			free (data->cmd->name);
		data->cmd->name = ft_strjoin(data->cmd->path, data->cmd->opt[0]);
		if (access(data->cmd->name, F_OK | X_OK) == 0)
		{
			ft_dbl_ptr_free((void **) data->path_names);
			close (data->error_fd);
			data->flag->execve = 1;
			clean_before_exit(data);
			execve(data->cmd->name, data->cmd->opt, data->env);
		}
		else
			make_some_free(data);
	}
	ft_dbl_ptr_free((void **)data->path_names);
	data->cmd->name = ft_strdup(data->cmd->opt[0]);
}

void	find_prog(t_vault *data, int line)
{
	if (is_built_in(data->cmd->name) == 1)
	{
		built_in(data, line);
		return ;
	}
	else if (access(data->cmd->name, F_OK | X_OK) == 0)
	{
		if (data->path_names)
			ft_dbl_ptr_free((void **) data->path_names);
		data->error_fd = open(".tmp_error", O_CREAT | O_WRONLY | O_TRUNC, 0644);//voir avec eric
		ft_putstr_fd("0\0", data->error_fd);
		close (data->error_fd);
		data->flag->execve = 1;
		clean_before_exit(data);
		execve(data->cmd->name, data->cmd->opt, data->env);
	}
	else if (access(data->cmd->name, F_OK | X_OK) != 0)
		cmd_path_check(data);
	error_message(data, "command not found", "127\0");
}

void	make_some_free(t_vault *data)
{
	free(data->cmd->name);
	free(data->cmd->path);
	return ;
}
