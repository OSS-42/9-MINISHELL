/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 16:06:21 by ewurstei          #+#    #+#             */
/*   Updated: 2022/12/01 23:00:02 by ewurstei         ###   ########.fr       */
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

void	ft_unset(t_vault *data, int row)
{
	int	j;

	while (data->rl_decomp[row])
	{
		if (check_error(data, row) == 1)
		{
			data->b_in->unset_arg = ft_join(data->rl_decomp[row], "=");
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
		else
		{
			ft_putstr_fd("unset : argument error\n", 2);
			return ;
		}
		row++;
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

void	ft_export(t_vault *data, int row)
{
	int	j;
	int	len;

	len = 0;
	if (!(data->rl_decomp[row]))
		order_env(data);
	else
	{
		while (data->rl_decomp[row])
		{
			if (ft_str_env_var(data->rl_decomp[row], '=') == 0)
			{
				printf("export : bad argument\n");
				return ;
			}
			data->b_in->export_arg = ft_strdup(data->rl_decomp[row]);
			if (ft_strchr(data->b_in->export_arg, '=') == NULL)
			{
				data->b_in->export_arg = ft_strjoin(data->rl_decomp[row], "=\"\"");
				data->b_in->export_var = ft_strjoin(data->rl_decomp[row], "=");
			}
			else
			{
				len = ft_strlen(data->rl_decomp[row])
					- ft_strlen(ft_strchr(data->rl_decomp[row], '=')) + 1;
				data->b_in->export_var = ft_substr(data->rl_decomp[row], 0, len);
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
			row++;
		}	
		return ;
	}
}

void	order_env(t_vault *data)
{
	int		rows;
	int		i;
	int		j;

	rows = ft_dbl_ptr_len(data->env);
	data->b_in->env_ord = ft_dbl_ptr_realloc(data->b_in->env_ord, rows + 1);
	i = -1;
	while (++i < rows)
		data->b_in->env_ord[i] = data->env[i];
	i = -1;
	while (++i < rows)
	{
		j = i;
		while (++j < rows)
		{
			if (ft_strcmp(data->b_in->env_ord[i], data->b_in->env_ord[j]) > 0)
			{
				data->b_in->order_var = ft_strdup(data->b_in->env_ord[i]);
				data->b_in->env_ord[i] = ft_strdup(data->b_in->env_ord[j]);
				data->b_in->env_ord[j] = ft_strdup(data->b_in->order_var);
			}
		}
	}
	ft_env(data, 2);
	return ;
}

//bizarrement ft_dbl_ptr_realloc n'aime pas le free si la table existe deja...