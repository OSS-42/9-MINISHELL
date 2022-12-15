/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:21:56 by ewurstei          #+#    #+#             */
/*   Updated: 2022/12/15 09:34:01 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	quote_priority(t_vault *data, int row)
{
	int	j;

	j = 0;
	data->b_in->echo_priority = 0;
	while (data->rl_decomp[row] && data->rl_decomp[row][j] != '\0')
	{
		if (data->rl_decomp[row][j] == '\"')
		{
			data->b_in->echo_dble_q++;
			if (data->b_in->echo_first == 0)
				data->b_in->echo_first = 2;
			if (data->b_in->echo_dble_q % 2 == 0 && data->b_in->echo_first == 2)
				data->b_in->echo_priority = 34;
		}
		else if (data->rl_decomp[row][j] == '\'')
		{
			data->b_in->echo_sgle_q++;
			if (data->b_in->echo_first == 0)
				data->b_in->echo_first = 1;
			if (data->b_in->echo_sgle_q % 2 == 0 && data->b_in->echo_first == 1)
				data->b_in->echo_priority = 39;
		}
		j++;
	}
	return ;
}

void	clean_quote(t_vault *data, int row)
{
	int		j;
	int		k;
	int		len;
	char	*temp;

	j = 0;
	k = 0;
	len = ft_strlen(data->rl_decomp[row]);
	temp = ft_calloc(len, sizeof(char));
	while (j < len)
	{
		if (data->rl_decomp[row][j] == data->b_in->echo_priority)
			j++;
		temp[k] = data->rl_decomp[row][j];
		j++;
		k++;
	}
	free (data->rl_decomp[row]);
	data->rl_decomp[row] = temp;
}

// void	split_on_char(t_vault *data, int row, char c)
// {
// 	int		i;
// 	char	*buffer;
// 	int		len;

// 	i = -1;
// 	if (data->b_in->echo_first == 1 && data->rl_decomp[row][++i] == '\'')
// 	{
// 		len = 0;
// 		while (data->rl_decomp[row][++i])
// 			len++;
// 		i = 0;
// 		while (data->rl_decomp[row][++i] && data->rl_decomp[row][i] != '\'')
// 			i++;
	// 	if (i == len)
	// 		return ;
	// 	else
	// 	{
	// 		data->split = ft_split(data->rl_decomp[row], '\'');
	// 		free (data->rl_decomp[row]);
	// 		i = 0;
	// 		while (data->split[i] && i < 1)
	// 		{
	// 			buffer = ft_strjoin("\'", data->split[i]);
	// 			free(data->split[i]);
	// 			data->split[i] = ft_strdup(buffer);
	// 			free(buffer);
	// 			buffer = ft_strjoin(data->split[i], "\'");
	// 			free (data->split[i]);
	// 			data->split[i] = ft_strdup(buffer);
	// 			free (buffer);
	// 			i++;
	// 		}
	// 		data->flag->split_char = '\'';
	// 		data->flag->split_count = ft_dbl_ptr_len(data->split);
	// 		data->flag->same_line = ft_dbl_ptr_len(data->split) - 1;
	// 		change_tab(data, row);
	// 		return ;
	// 	}
	// }
	// else if (data->b_in->echo_sgle_q > 0 && data->rl_decomp[row][0] != '\'')
	// {
	// 	data->split = ft_split(data->rl_decomp[row], '\'');
	// 	free (data->rl_decomp[row]);
	// 	i = 1;
	// 	while (data->split[i])
	// 	{
	// 		buffer = ft_strjoin("\'", data->split[i]);
	// 		free(data->split[i]);
	// 		data->split[i] = ft_strdup(buffer);
// 			free(buffer);
// 			buffer = ft_strjoin(data->split[i], "\'");
// 			free (data->split[i]);
// 			data->split[i] = ft_strdup(buffer);
// 			free (buffer);
// 			i++;
// 		}
// 		data->flag->split_char = '\'';
// 		data->flag->split_count = ft_dbl_ptr_len(data->split);
// 		data->flag->same_line = ft_dbl_ptr_len(data->split) - 1;
// 		change_tab(data, row);
// 		return ;
// 	}
// 	data->flag->split_char = c;
// 	data->split = ft_split(data->rl_decomp[row], c);
// 	free (data->rl_decomp[row]);
// 	data->flag->split_count = ft_dbl_ptr_len(data->split);
// 	data->flag->same_line = ft_dbl_ptr_len(data->split) - 1;
// 	if (c == '$')
// 	{
// 		data->flag->same_line = ft_dbl_ptr_len(data->split) - 1;
// 		i = 0;
// 		while (data->split[i])
// 		{
// 			buffer = ft_strjoin("$", data->split[i]);
// 			free(data->split[i]);
// 			data->split[i] = ft_strdup(buffer);
// 			free(buffer);
// 			i++;
// 		}
// 	}
// 	change_tab(data, row);
// 	return ;
// }

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

// void	change_tab(t_vault *data, int row)
// {
// 	int		i;
// 	char	**temp;

// 	i = 0;
// 	temp = NULL;
// 	temp = ft_calloc(sizeof(char *), ft_dbl_ptr_len(data->rl_decomp)
// 			+ ft_dbl_ptr_len(data->split) + 1);
// 	while (i < row)
// 	{
// 		temp[i] = ft_strdup(data->rl_decomp[i]);
// 		free (data->rl_decomp[i]);
// 		i++;
// 	}
// 	i = insert_row(i, data->flag->split_count + 1, temp, data->split);
// 	while (i < ft_dbl_ptr_len(data->rl_decomp) && data->rl_decomp[i + 1])
// 	{
// 		temp[i] = ft_strdup(data->rl_decomp[i + 1]);
// 		free (data->rl_decomp[i + 1]);
// 		i++;
// 	}
// 	free (data->rl_decomp);
// 	data->rl_decomp = ft_dbl_ptr_realloc(data->rl_decomp, ft_dbl_ptr_len(temp) + 1);
// 	i = 0;
// 	while (temp[i])
// 	{
// 		data->rl_decomp[i] = ft_strdup(temp[i]);
// 		free (temp[i]);
// 		i++;
// 	}
// 	free (temp);
// }
