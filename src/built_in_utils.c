/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 21:08:51 by ewurstei          #+#    #+#             */
/*   Updated: 2023/01/20 08:34:13 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	join_unset(t_vault *data, int line)
{
	int	j;

	ft_free_n_null (data->b_in->unset_arg);
	data->b_in->unset_arg = ft_strjoin(data->cmd->opt[line], "=");
	j = 0;
	while (data->env[j])
	{
		if (ft_strnstr(data->env[j], data->b_in->unset_arg,
				ft_strlen(data->b_in->unset_arg)) == NULL)
			j++;
		else
		{
			remove_line_env(data, j);
			ft_free_n_null (data->b_in->unset_arg);
			data->b_in->unset_arg = NULL;
			return ;
		}
	}
	ft_free_n_null (data->b_in->unset_arg);
	data->b_in->unset_arg = NULL;
	return ;
}

void	swap_lines(t_vault *data, int rows)
{
	int		i;
	int		j;
	char	*temp;

	i = -1;
	while (++i < rows)
	{
		j = i;
		while (++j < rows)
		{
			if (ft_strcmp(data->b_in->env_ord[i], data->b_in->env_ord[j]) > 0)
			{
				temp = ft_strdup(data->b_in->env_ord[i]);
				ft_free_n_null (data->b_in->env_ord[i]);
				data->b_in->env_ord[i] = NULL;
				data->b_in->env_ord[i] = ft_strdup(data->b_in->env_ord[j]);
				ft_free_n_null (data->b_in->env_ord[j]);
				data->b_in->env_ord[j] = NULL;
				data->b_in->env_ord[j] = ft_strdup(temp);
				ft_free_n_null (temp);
			}
		}
	}
	return ;
}

void	dup_env(t_vault *data)
{
	int	j;

	j = 0;
	while (data->env[j])
	{
		free(data->b_in->env_export[j]);
		data->b_in->env_export[j] = ft_strdup(data->env[j]);
		j++;
	}
	data->b_in->env_export[j] = ft_strdup(data->b_in->exp_arg);
	ft_free_n_null (data->b_in->exp_arg);
	data->b_in->exp_arg = NULL;
	ft_dbl_ptr_free((void **)data->env);
	data->env = ft_dbl_ptr_copy(data->b_in->env_export);
	ft_dbl_ptr_free((void **)data->b_in->env_export);
	return ;
}

void	var_prep(t_vault *data, int line)
{
	free(data->b_in->exp_arg);
	data->b_in->exp_arg = ft_strjoin(data->cmd->opt[line], "=\0");
	data->b_in->export_var = ft_strjoin(data->cmd->opt[line], "=");
	return ;
}

void	copy_env(t_vault *data, char **temp, int i)
{
	int	j;

	j = -1;
	temp[i] = ft_calloc(sizeof(char), ft_strlen(data->env[i]) + 15);
	while (data->env[i][++j] != '\0' && data->env[i][j] != '=')
		temp[i][j] = data->env[i][j];
	temp[i][j] = data->env[i][j];
}
