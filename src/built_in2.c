/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 16:06:21 by ewurstei          #+#    #+#             */
/*   Updated: 2022/12/02 15:47:28 by ewurstei         ###   ########.fr       */
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
			data->b_in->unset_arg = ft_strjoin(data->rl_decomp[row], "=");
			j = 0;
			while (data->env[j])
			{
				if (ft_strnstr(data->env[j], data->b_in->unset_arg,
						ft_strlen(data->b_in->unset_arg)) == NULL)
					j++;
				else
				{
					remove_line_env(data, j);
					free (data->b_in->unset_arg);
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
			data->env[j] = ft_strdup(data->b_in->exp_arg);
			free(data->b_in->exp_arg);
			return ;
		}
	}
	data->b_in->env_export = ft_calloc(j + 2, sizeof(char *));
	j = 0;
	while (data->env[j])
	{
		data->b_in->env_export[j] = ft_strdup(data->env[j]);
		j++;
	}
	data->b_in->env_export[j] = ft_strdup(data->b_in->exp_arg);
	free (data->b_in->exp_arg);
	data->env = &data->b_in->env_export[0];
	return ;
}

void	ft_export(t_vault *data, int row)
{
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
			data->b_in->exp_arg = ft_strdup(data->rl_decomp[row]);
			if (ft_strchr(data->b_in->exp_arg, '=') == NULL)
			{
				data->b_in->exp_arg = ft_strjoin(data->rl_decomp[row], "=\"\"");
				data->b_in->export_var = ft_strjoin(data->rl_decomp[row], "=");
			}
			else
				data->b_in->export_var = ft_substr(data->rl_decomp[row], 0,
						ft_strlen(data->rl_decomp[row])
						- ft_strlen(ft_strchr(data->rl_decomp[row], '=')) + 1);
			add_line_env(data);
			row++;
		}
	}
}

void	order_env(t_vault *data)
{
	int		rows;
	int		i;

	rows = ft_dbl_ptr_len(data->env);
	data->b_in->env_ord = ft_dbl_ptr_realloc(data->b_in->env_ord, rows + 1);
	i = -1;
	while (++i < rows)
		data->b_in->env_ord[i] = ft_strjoin("declare -x ", data->env[i]);
	swap_lines(data, rows);
	ft_env(data, 2);
	return ;
}

//bizarrement ft_dbl_ptr_realloc n'aime pas le free si la table existe deja...