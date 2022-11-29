/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 16:06:21 by ewurstei          #+#    #+#             */
/*   Updated: 2022/11/28 21:48:23 by ewurstei         ###   ########.fr       */
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
	data->b_in->env_unset = ft_calloc(rows, sizeof(char *));
	j = 0;
	rows = 0;
	while (data->env[rows])
	{
		if (rows == i)
			rows++;
		if (data->env[rows])
			data->b_in->env_unset[j] = ft_strdup(data->env[rows]);
		else
			break ;
		rows++;
		j++;
	}
	data->env = &data->b_in->env_unset[0];
	return ;
}

void	ft_unset(t_vault *data)
{
	int	i;
	int	j;

	i = 1;
	while (data->rl_decomp[i])
	{
		if (!(data->rl_decomp[i]) || ft_is_env_var(data->rl_decomp[i], 0) == 0)
		{
			ft_putstr_fd("unset : argument error\n", 2);
			return ;
		}
		else
		{
			data->b_in->unset_arg = ft_join(data->rl_decomp[i], "=");
			j = 0;
			while (data->env[j])
			{
				if (ft_strnstr(data->env[j], data->b_in->unset_arg,
						ft_strlen(data->b_in->unset_arg)) == NULL)
					j++;
				else
				{
					remove_line_env(data, j);
					break ;
				}
			}
		}
		i++;
	}
	return ;
}

void	add_line_env(t_vault *data, int i)
{
	data->b_in->env_export = ft_calloc(i + 2, sizeof(char *));
	i = 0;
	while (data->env[i])
	{
		data->b_in->env_export[i] = ft_strdup(data->env[i]);
		i++;
	}
	data->b_in->env_export[i] = ft_strdup(data->b_in->export_arg);
	data->env = &data->b_in->env_export[0];
	return ;
}

void	ft_export(t_vault *data)
{
	int	i;
	int	j;
	int	len;

	i = 1;
	len = 0;
	if (!(data->rl_decomp[i]))
		order_env(data);
	else
	{
		while (data->rl_decomp[i])
		{
			if (ft_is_env_var(data->rl_decomp[i], '=') == 0)
			{
				printf("export : bad argument\n");
				return ;
			}
			data->b_in->export_arg = ft_strdup(data->rl_decomp[i]);
			if (ft_strchr(data->b_in->export_arg, '=') == NULL)
			{
				data->b_in->export_arg = ft_strjoin(data->rl_decomp[i], "=\"\"");
				data->b_in->export_var = ft_strjoin(data->rl_decomp[i], "=");
			}
			else
			{
				len = ft_strlen(data->rl_decomp[i])
					- ft_strlen(ft_strchr(data->rl_decomp[i], '='));
				data->b_in->export_var = ft_substr(data->rl_decomp[i], 0, len + 1);
			}
			j = 0;
			while (data->env[j])
			{
				if (ft_strnstr(data->env[j], data->b_in->export_var,
						ft_strlen(data->b_in->export_var)) == NULL)
					j++;
				else
				{
					data->env[j] = ft_strdup(data->b_in->export_arg);
					free(data->b_in->export_arg);
					return ;
				}
			}
			add_line_env(data, j);
			i++;
		}	
		return ;
	}
}

void	order_env(t_vault *data)
{
	int		rows;
	int		i;
	int		j;

	i = 0;
	rows = 0;
	while (data->env[rows])
		rows++;
	if (data->b_in->env_order)
		free_dbl_ptr((void **)data->b_in->env_order);
	data->b_in->env_order = ft_calloc(rows + 1, sizeof(char *));
	while (data->env[i])
	{
		data->b_in->env_order[i] = data->env[i];
		i++;
	}
	i = 0;
	while (i < rows)
	{
		j = i + 1;
		while (j < rows)
		{
			if (ft_strcmp(data->b_in->env_order[i],
					data->b_in->env_order[j]) > 0)
			{
				data->b_in->order_var = ft_strdup(data->b_in->env_order[i]);
				data->b_in->env_order[i] = ft_strdup(data->b_in->env_order[j]);
				data->b_in->env_order[j] = ft_strdup(data->b_in->order_var);
			}
			j++;
		}
		i++;
	}
	ft_env(data, 2);
	return ;
}
