/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbertin <mbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:21:56 by ewurstei          #+#    #+#             */
/*   Updated: 2023/01/11 12:05:51 by mbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	dollar_var_to_expand(t_vault *data, int row, int i)
{
	char	*temp;

	temp = NULL;
	if (ft_char_env_var(data->rl_dec[row][i + 1]) != 1)
	{
		if (data->rl_dec[row][i + 1] == '?')
		{
			temp = find_error_code(data);
			data->dollar_var_len = ft_strlen(temp);
		}
		else
			return (i);
	}
	if (!temp)
		temp = var_extract(data, row, i + 1);
	if (data->flag->var_not_found == 1)
		return (0);
	copy_buffer(data, temp);
	ft_free_n_null (temp);
	return (0);
}

char	*var_extract(t_vault *data, int row, int position)
{
	int		k;
	char	*temp;

	temp = NULL;
	k = position;
	data->dollar_var_len = 0;
	while (data->rl_dec[row][k]
		&& ft_char_env_var(data->rl_dec[row][k]) == 1)
	{
		data->dollar_var_len++;
		k++;
	}
	if (data->dollar_var_len > 0)
	{
		temp = ft_substr(data->rl_dec[row], position,
				data->dollar_var_len);
		data->dollar_var = ft_strjoin(temp, "=");
		ft_free_n_null (temp);
		temp = NULL;
	}
	else
		return (NULL);
	temp = does_var_exist(data);
	return (temp);
}

char	*does_var_exist(t_vault *data)
{
	int		i;
	char	*temp;

	i = 0;
	temp = ft_calloc(sizeof(char), 500);
	while (data->env[i])
	{
		if (ft_strnstr(data->env[i], data->dollar_var,
				ft_strlen(data->dollar_var) + 1) == NULL)
			data->flag->var_not_found = 1;
		else
		{
			data->flag->var_not_found = 0;
			break ;
		}
		i++;
	}
	ft_free_n_null (temp);
	temp = expand_var(data, i);
	return (temp);
}

char	*expand_var(t_vault *data, int row_var)
{
	int		len_var;
	char	*temp;

	temp = NULL;
	if (data->flag->var_not_found == 1)
	{
		ft_free_n_null (data->dollar_var);
		data->dollar_var = NULL;
		return (temp);
	}
	else
	{
		len_var = ft_strlen(data->env[row_var]) - data->dollar_var_len;
		temp = ft_substr(data->env[row_var],
				data->dollar_var_len + 1, len_var);
		ft_free_n_null (data->dollar_var);
		data->dollar_var = NULL;
	}
	return (temp);
}

void	copy_buffer(t_vault *data, char *temp)
{
	int	k;

	k = -1;
	while (temp[++k])
	{
		data->buffer[data->pos] = temp[k];
		data->pos++;
	}
}
