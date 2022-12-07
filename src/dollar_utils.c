/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbertin <mbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:21:56 by ewurstei          #+#    #+#             */
/*   Updated: 2022/12/07 09:21:07 by mbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	copy_var(char *dest, char *source, int pos)
{
	int		k;

	k = 0;
	while (source[k])
	{
		dest[pos] = source[k];
		k++;
		pos++;
	}
	return (pos);
}

void	var_to_value(t_vault *data, int row, char *temp)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (data->rl_decomp[row][j])
	{
		if (data->rl_decomp[row][j] == '$' && data->flag->runs != 1)
		{
			i = copy_var(temp, data->dollar_var, i);
			data->flag->runs = 1;
			j = j + data->dollar_var_len;
			free (data->dollar_var);
		}
		else
		{
			temp[i] = data->rl_decomp[row][j];
			i++;
		}
		j++;
	}
}

void	split_on_dollar(t_vault *data, int row)
{
	int		i;
	char	**temp;
	char	*buffer;

	i = 0;
	temp = NULL;
	data->split_dollar = ft_split(data->rl_decomp[row], '$');
	free (data->rl_decomp[row]);
	data->flag->dollar_split = 1;
	while (data->split_dollar[i])
	{
		buffer = ft_strjoin("$", data->split_dollar[i]);
		free(data->split_dollar[i]);
		data->split_dollar[i] = ft_strdup(buffer);
		free(buffer);
		i++;
	}
	temp = ft_calloc(sizeof(char *), ft_dbl_ptr_len(data->rl_decomp)
			+ ft_dbl_ptr_len(data->split_dollar));
	change_tab(data, temp, row);
	return ;
}

int	insert_row(int pos, int count, char **dest, char **source)
{
	int	m;

	m = 0;
	while (m < count)
	{
		dest[pos] = ft_strdup(source[m]);
		free (source[m]);
		pos++;
		m++;
	}
	free (source);
	return (pos);
}

void	change_tab(t_vault *data, char **dest, int row)
{
	int	i;

	i = 0;
	while (i < row)
	{
		dest[i] = ft_strdup(data->rl_decomp[i]);
		free (data->rl_decomp[i]);
		i++;
	}
	i = insert_row(i, data->flag->dollar_count, dest, data->split_dollar);
	while (i < ft_dbl_ptr_len(data->rl_decomp) && data->rl_decomp[i + 1])
	{
		dest[i] = ft_strdup(data->rl_decomp[i + 1]);
		free (data->rl_decomp[i + 1]);
		i++;
	}
	free (data->rl_decomp);
	data->rl_decomp = ft_dbl_ptr_realloc(data->rl_decomp, i + 1);
	i = 0;
	while (dest[i])
	{
		data->rl_decomp[i] = ft_strdup(dest[i]);
		free (dest[i]);
		i++;
	}
	free (dest);
}
