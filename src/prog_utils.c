/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prog_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 10:27:46 by ewurstei          #+#    #+#             */
/*   Updated: 2023/01/12 17:25:57 by ewurstei         ###   ########.fr       */
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
		ft_free_n_null (data->paths);
		data->paths = NULL;
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
		cmd_prep(data, i);
		if (access(data->cmd->name, F_OK | X_OK) == 0)
		{
			if (data->path_names)
				ft_dbl_ptr_free((void **) data->path_names);
			put_code_in_fd("0\0", data->error_fd);
			data->flag->execve = 1;
			clean_before_exit(data);
			execve(data->cmd->name, data->cmd->opt, data->env);
			execve_fail(data);
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
		data->flag->exit_fork = 1;
		built_in(data, line);
		return ;
	}
	else if (access(data->cmd->name, F_OK | X_OK) == 0)
	{
		if (data->path_names)
			ft_dbl_ptr_free((void **) data->path_names);
		put_code_in_fd("0\0", data->error_fd);
		data->flag->execve = 1;
		clean_before_exit(data);
		execve(data->cmd->name, data->cmd->opt, data->env);
		execve_fail(data);
	}
	else if (access(data->cmd->name, F_OK | X_OK) != 0)
		cmd_path_check(data);
	error_message(data, "command not found", "127\0");
}

void	make_some_free(t_vault *data)
{
	ft_free_n_null(data->cmd->name);
	data->cmd->name = NULL;
	ft_free_n_null(data->cmd->path);
	data->cmd->path = NULL;
	return ;
}

void	in_child_exec(t_vault *data, int line)
{
	final_quotes_removing(data, line);
	data->cmd->name = ft_strdup(data->cmd->opt[0]);
	recompose_tab_arg(data, line);
	close_pipe(data);
	find_prog(data, line);
	exit_process(data);
}
