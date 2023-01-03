/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 16:06:21 by ewurstei          #+#    #+#             */
/*   Updated: 2023/01/03 00:07:47 by ewurstei         ###   ########.fr       */
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

void	ft_unset(t_vault *data, int line)
{
	while (data->cmd->opt[line])
	{
		if (check_error(data, line) == 0)
			error_message(data, "missing or wrong arguments", "2\0");
		join_unset(data, line);
		line++;
	}
	return ;
}

void	add_line_env(t_vault *data)
{
	int	j;

	j = 0;
	while (data->env[j])
	{
		if (ft_strnstr(data->env[j], data->b_in->export_var,
				ft_strlen(data->b_in->export_var)) == NULL)
			j++;
		else
		{
			free (data->env[j]);
			data->env[j] = ft_strdup(data->b_in->exp_arg);
			free(data->b_in->exp_arg);
			return ;
		}
	}
	data->b_in->env_export = ft_dbl_ptr_realloc(data->b_in->env_export, j + 2);
	dup_env(data);
	data->b_in->env_export[j] = ft_strdup(data->b_in->exp_arg);
	free (data->b_in->exp_arg);
	data->env = &data->b_in->env_export[0];
	return ;
}

void	ft_export(t_vault *data, int line)
{
	if (!(data->cmd->opt[line + 1]))
		order_env(data);
	else
	{
		while (data->cmd->opt[++line])
		{
			if (ft_str_env_var(data->cmd->opt[line], '=') == 0)
				error_message(data, "missing or wrong arguments", "2\0");
			if (data->b_in->export_var)
				free(data->b_in->export_var);
			data->b_in->exp_arg = ft_strdup(data->cmd->opt[line]);
			if (ft_strchr(data->b_in->exp_arg, '=') == NULL)
				var_prep(data, line);
			else
				data->b_in->export_var = ft_substr(data->cmd->opt[line], 0,
						ft_strlen(data->cmd->opt[line])
						- ft_strlen(ft_strchr(data->cmd->opt[line], '=')) + 1);
			add_line_env(data);
		}
	}
}

void	order_env(t_vault *data)
{
	int		rows;
	int		i;
	char	**temp;
	char	*buff2;

	rows = ft_dbl_ptr_len(data->env);
	temp = NULL;
	temp = ft_dbl_ptr_realloc(temp, rows + 1);
	data->b_in->env_ord = ft_dbl_ptr_realloc(data->b_in->env_ord, rows + 1);
	buff2 = NULL;
	i = -1;
	while (++i < rows)
	{
		copy_env(data, temp, i);
		export_only_format(data, buff2, temp, i);
		free (data->b_in->env_ord[i]);
		data->b_in->env_ord[i] = ft_strdup(temp[i]);
		free(temp[i]);
	}
	free (temp);
	swap_lines(data, rows);
	ft_env(data, 2);
	return ;
}
