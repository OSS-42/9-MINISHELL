/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 16:06:21 by ewurstei          #+#    #+#             */
/*   Updated: 2022/11/23 16:54:19 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	remove_line_env(t_vault *data, int i)
{
	int		j;
	int		rows;

	rows = 0;
	j = 0;
	while (data->env[rows])
		rows++;
	data->env_unset = malloc(sizeof(char *) * rows);
	rows = 0;
	while (data->env[rows])
	{
		if (rows == i)
			rows++;
		data->env_unset[j] = ft_strdup(data->env[rows]);
		rows++;
		j++;
	}
	data->env = &data->env_unset[0];
	return ;
}

void	ft_unset(t_vault *data)
{
	int	i;

	i = 0;
	if (!(data->readline_decomposer[1]))
		perror("unset");
	else
	{
		data->unset_arg = ft_join(data->readline_decomposer[1], "=");
		while (data->env[i])
		{
			if (ft_strnstr(data->env[i], data->unset_arg,
					ft_strlen(data->unset_arg)) == NULL)
				i++;
			else
				remove_line_env(data, i);
		}
	}
	return ;
}

void	add_line_env(t_vault *data)
{
	int	rows;

	rows = 0;
	while (data->env[rows])
		rows++;
	data->env_export = malloc(sizeof(char *) * rows + 1);
	rows = 0;
	while (data->env[rows])
	{
		data->env_export[rows] = ft_strdup(data->env[rows]);
		rows++;
	}
	data->env_export[rows] = ft_strdup(data->export_arg);
	data->env_export[rows + 1] = "\0";
	data->env = &data->env_unset[0];
	return ;
}

void	ft_export(t_vault *data)
{
	int	i;

	i = 0;
	if (!(data->readline_decomposer[1]))
		ft_env(data);
	else
	{
		data->export_arg = ft_join(data->readline_decomposer[1], "=");
		if (!(data->readline_decomposer[2]))
			data->export_arg = ft_join(data->readline_decomposer[2], "");
		else
			data->export_arg = ft_join(data->readline_decomposer[2], data->readline_decomposer[3]);
		while (data->env[i])
		{
			if (ft_strnstr(data->env[i], data->readline_decomposer[0],
					ft_strlen(data->readline_decomposer[0])) == NULL)
				i++;
			else
				data->env[i] = ft_strdup(data->export_arg);
		}
		add_line_env(data);
		return ;
	}	
}
