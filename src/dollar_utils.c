/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbertin <mbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:21:56 by ewurstei          #+#    #+#             */
/*   Updated: 2022/12/07 16:38:58 by mbertin          ###   ########.fr       */
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

void	split_on_char(t_vault *data, int row, char c)
{
	int		i;
	char	**temp;
	char	*buffer;

	i = 0;
	temp = NULL;
	data->flag->split_char = c;
	data->split = ft_split(data->rl_decomp[row], c);
	free (data->rl_decomp[row]);
	data->flag->split_count = 1;
	if (c == '$')
	{
		while (data->split[i])
		{
			buffer = ft_strjoin("$", data->split[i]);
			free(data->split[i]);
			data->split[i] = ft_strdup(buffer);
			free(buffer);
			i++;
		}
	}
	else if (c == '>')
	{
		if (ft_dbl_ptr_len(data->split) > data->flag->chevron_count)
			i = i + 1;
		if (data->flag->chevron_with_space == 0)
		{
			while (data->split[i])
			{
				buffer = ft_strjoin(">", data->split[i]);
				free(data->split[i]);
				data->split[i] = ft_strdup(buffer);
				free(buffer);
				i++;
			}
		}
		// else
		// {
		// 	while (data->flag->chevron_with_space != 0)
		// 	{
		// 		i = i + 1;
		// 		while (data->split[i])
		// 		{
		// 			buffer = ft_strjoin(">", data->split[i]);
		// 			free(data->split[i]);
		// 			data->split[i] = ft_strdup(buffer);
		// 			free (buffer);
		// 			i++;
		// 		}
		// 		data->flag->chevron_with_space--;
		// 	}
		// }
	}
	temp = ft_calloc(sizeof(char *), ft_dbl_ptr_len(data->rl_decomp)
			+ ft_dbl_ptr_len(data->split) + 1);
	change_tab(data, temp, row);
	return ;
}

int	insert_row(int pos, int count, char **dest, char **source)
{
	int	m;

	m = 0;
	while (m < count && source[m])
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
	if (data->flag->split_char == '$')
		i = insert_row(i, data->flag->dollar_count, dest, data->split);
	else if (data->flag->split_char == '>')
		i = insert_row(i, data->flag->chevron_count + 1, dest, data->split);
	while (i < ft_dbl_ptr_len(data->rl_decomp) && data->rl_decomp[i + 1])
	{
		dest[i] = ft_strdup(data->rl_decomp[i + 1]);
		free (data->rl_decomp[i + 1]);
		i++;
	}
	free (data->rl_decomp);
	data->rl_decomp = ft_dbl_ptr_realloc(data->rl_decomp, ft_dbl_ptr_len(dest) + 1);
	i = 0;
	while (dest[i])
	{
		data->rl_decomp[i] = ft_strdup(dest[i]);
		free (dest[i]);
		i++;
	}
	free (dest);
}
