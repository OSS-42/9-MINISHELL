/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 16:06:21 by ewurstei          #+#    #+#             */
/*   Updated: 2022/11/23 16:06:29 by ewurstei         ###   ########.fr       */
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