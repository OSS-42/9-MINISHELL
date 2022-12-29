/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   explore_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 23:49:56 by ewurstei          #+#    #+#             */
/*   Updated: 2022/12/29 17:22:16 by ewurstei         ###   ########.fr       */
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
		ft_export (data, line + 1);
	if (ft_strcmp("unset", data->cmd->name) == 0)
		ft_unset (data, line);
	if (ft_strcmp("exit", data->cmd->name) == 0)
		ft_exit (data);
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
	data->tab_arg[line] = NULL;
	if (data->cmd->opt[i])
		data->tab_arg[line] = ft_strdup(data->cmd->opt[i]);
	else
		return ;
	i++;
	while (data->cmd->opt[i])
	{
		buffer = ft_strjoin(data->tab_arg[line], " ");
		data->tab_arg[line] = NULL;
		data->tab_arg[line] = ft_strjoin(buffer, data->cmd->opt[i]);
		free (buffer);
		i++;
	}
}
