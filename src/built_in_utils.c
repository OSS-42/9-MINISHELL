/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 21:08:51 by ewurstei          #+#    #+#             */
/*   Updated: 2022/12/05 16:39:14 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	join_unset(t_vault *data, int row)
{
	int	j;

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
				free (data->b_in->env_ord[i]);
				data->b_in->env_ord[i] = ft_strdup(data->b_in->env_ord[j]);
				free (data->b_in->env_ord[j]);
				data->b_in->env_ord[j] = ft_strdup(temp);
				free (temp);
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
	return ;
}

void	var_prep(t_vault *data, int row)
{
	free(data->b_in->exp_arg);
	data->b_in->exp_arg = ft_strjoin(data->rl_decomp[row], "=\"\"");
	data->b_in->export_var = ft_strjoin(data->rl_decomp[row], "=");
	return ;
}

// void	var_extract(t_vault *data, int row, int position)
// {
// 	int		k;
// 	char	*temp;

// 	k = position + 1;
// 	while (data->rl_decomp[row][k] != ' ' && data->rl_decomp[row][k]
// 		&& ft_char_env_var(data->rl_decomp[row][k]) == 1)
// 	{
// 		data->dollar_var_len++;
// 		k++;
// 	}
// 	temp = ft_substr(data->rl_decomp[row], position + 1, data->dollar_var_len);
// 	data->dollar_var = ft_strjoin(temp, "=");
// 	free (temp);
// 	return ;
// }

void	var_extract(t_vault *data, int row, int position, char **array)
{
	int		k;
	char	*temp;

	k = position + 1;
	while (array[row][k] != ' ' && array[row][k]
			&& ft_char_env_var(array[row][k]) == 1)
	{
		data->dollar_var_len++;
		k++;
	}
	temp = ft_substr(array[row], position + 1, data->dollar_var_len);
	data->dollar_var = ft_strjoin(temp, "=");
	free (temp);
	return ;
}