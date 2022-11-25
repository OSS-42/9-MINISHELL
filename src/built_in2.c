/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 16:06:21 by ewurstei          #+#    #+#             */
/*   Updated: 2022/11/24 22:45:38 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	remove_line_env(t_vault *data, int i)
{
	int		j;
	int		rows;

	rows = 0;
	while (data->env[rows])
		rows++;
	if (data->env_unset)
		free_dbl_ptr((void **) data->env_unset);
	data->env_unset = ft_calloc(rows, sizeof(char *));
	j = 0;
	rows = 0;
	while (data->env[rows])
	{
		if (rows == i)
			rows++;
		if (data->env[rows])
			data->env_unset[j] = ft_strdup(data->env[rows]);
		else
			break ;
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
	if (!(data->rl_decomp[1]) || ft_strchr(data->rl_decomp[1], '=') != NULL)
		ft_putstr_fd("unset : argument error\n", 2);
	else
	{
		data->unset_arg = ft_join(data->rl_decomp[1], "=");
		printf("%s\n", data->unset_arg);
		while (data->env[i])
		{
			if (ft_strnstr(data->env[i], data->unset_arg,
					ft_strlen(data->unset_arg)) == NULL)
				i++;
			else
			{
				remove_line_env(data, i);
				return ;
			}
		}
	}
	return ;
}

void	add_line_env(t_vault *data, int i)
{
	if (data->env_export)
		free_dbl_ptr((void **)data->env_export);
	data->env_export = ft_calloc(i + 2, sizeof(char *));
	i = 0;
	while (data->env[i])
	{
		data->env_export[i] = ft_strdup(data->env[i]);
		i++;
	}
	data->env_export[i] = ft_strdup(data->export_arg);
	data->env = &data->env_export[0];
	return ;
}

void	ft_export(t_vault *data)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (!(data->rl_decomp[1]))
		order_env(data);
	else
	{
		data->export_arg = ft_strdup(data->rl_decomp[1]);
		if (ft_strchr(data->export_arg, '=') == NULL)
		{
			data->export_arg = ft_strjoin(data->rl_decomp[1], "=\"\"");
			data->export_var = ft_strjoin(data->rl_decomp[1], "=");
		}
		else
		{
			len = ft_strlen(data->rl_decomp[1]) - ft_strlen(ft_strchr(data->rl_decomp[1], '='));
			data->export_var = ft_substr(data->rl_decomp[1], 0, len + 1);
		}
		while (data->env[i])
		{
			if (ft_strnstr(data->env[i], data->export_var,
					ft_strlen(data->export_var)) == NULL)
				i++;
			else
			{
				data->env[i] = ft_strdup(data->export_arg);
				return ;
			}
		}
		add_line_env(data, i);
		return ;
	}	
}

void	order_env(t_vault *data)
{
	int		rows;
	int		i;
	int		j;

	i = 0;
	j = 0;
	rows = 0;
	while (data->env[rows])
		rows++;
	if (data->env_order)
		free_dbl_ptr((void **)data->env_order);
	data->env_order = ft_calloc(rows + 1, sizeof(char *));
	while (i < rows)
	{
		j = i + 1;
		while (j < rows)
		{
			if (ft_strcmp(data->env[i], data->env[j]) > 0)
			{
				if (data->order_var)
					free(data->order_var);
				data->order_var = ft_calloc(ft_strlen(data->env[i]), sizeof(char));
				ft_strcpy(data->order_var, data->env[i]);
				free (data->env[i]);
				data->env[i] = ft_calloc (ft_strlen(data->env[i + 1]), sizeof(char));
				ft_strcpy(data->env[i], data->env[i + 1]);
				free (data->env[i + 1]);
				data->env[i + 1] = ft_calloc(ft_strlen(data->order_var), sizeof(char));
				ft_strcpy(data->env[i + 1], data->order_var);
			}
			j++;
		}
		i++;
	}
	return ;
}