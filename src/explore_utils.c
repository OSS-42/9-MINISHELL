/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   explore_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbertin <mbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 23:49:56 by ewurstei          #+#    #+#             */
/*   Updated: 2023/01/12 08:54:56 by mbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	built_in(t_vault *data, int line)
{
	if (ft_strcmp("cd", data->cmd->name) == 0)
		ft_cd(data);
	if (ft_strcmp("pwd", data->cmd->name) == 0)
		ft_pwd(data);
	if (ft_strcmp("echo", data->cmd->name) == 0)
		ft_echo(data, line);
	if (ft_strcmp("env", data->cmd->name) == 0)
		ft_env (data, 1);
	if (ft_strcmp("export", data->cmd->name) == 0)
		ft_export (data, line);
	if (ft_strcmp("unset", data->cmd->name) == 0)
		ft_unset (data, line);
	if (ft_strcmp("exit", data->cmd->name) == 0)
	{
		ft_exit (data);
	}
	return ;
}

int	is_built_in(char *str)
{
	if (ft_strcmp("cd", str) == 0
		|| ft_strcmp("pwd", str) == 0
		|| ft_strcmp("echo", str) == 0
		|| ft_strcmp("env", str) == 0
		|| ft_strcmp("export", str) == 0
		|| ft_strcmp("unset", str) == 0
		|| ft_strcmp("exit", str) == 0)
		return (TRUE);
	return (FALSE);
}

void	recompose_tab_arg(t_vault *data, int line)
{
	char	*buffer;
	int		i;

	i = 1;
	buffer = NULL;
	if (data->cmd->opt[i])
		copy_cmd(data, line, i);
	else
		return ;
	if (data->cmd->opt[++i])
	{
		while (data->cmd->opt[i])
		{
			buffer = ft_strjoin(data->tab_arg[line], " ");
			ft_free_n_null (data->tab_arg[line]);
			data->tab_arg[line] = ft_strjoin(buffer, data->cmd->opt[i]);
			free (buffer);
			i++;
		}
	}
	else
		return ;
}

void	copy_cmd(t_vault *data, int line, int i)
{
	ft_free_n_null (data->tab_arg[line]);
	data->tab_arg[line] = NULL;
	data->tab_arg[line] = ft_strdup(data->cmd->opt[i]);
}

int	is_special_built_in(t_vault *data, int line)
{
	if (ft_strcmp(data->cmd->name, "cd") == 0
		|| (ft_strcmp(data->cmd->name, "exit") == 0
			&& !(data->tab_arg[line + 1]))
		|| ft_strcmp(data->cmd->name, "unset") == 0
		|| ft_strcmp(data->cmd->name, "export") == 0
		|| ft_strcmp(data->cmd->name, "pwd") == 0
		|| ft_strcmp(data->cmd->name, "env") == 0)
		return (TRUE);
	return (FALSE);
}
