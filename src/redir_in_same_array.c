/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in_same_array.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbertin <mbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 08:50:08 by mbertin           #+#    #+#             */
/*   Updated: 2023/01/20 12:27:09 by mbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	redir_in_same_array(t_vault *data, int i, int *j, char c)
{
	data->flag->chevron = c;
	if (c == '>' && data->tab_arg[i][*j + 1] == c)
	{
		data->flag->append = TRUE;
		data->tab_arg[i] = clean_the_chevron(data, data->tab_arg[i], 0, 0);
		find_redir_in_same_array(data, data->tab_arg[i], i, *j);
	}
	else if (c == '<' && data->tab_arg[i][*j + 1] == c)
	{
		data->tab_arg[i] = clean_the_chevron(data, data->tab_arg[i], 0, 0);
		find_redir_in_same_array(data, data->tab_arg[i], i, *j);
		data->flag->heredoc = TRUE;
	}
	else
		find_redir_in_same_array(data, data->tab_arg[i], i, *j);
	clean_redir(data, i);
	data->tab_arg[i] = clean_the_chevron(data, data->tab_arg[i], i, 0);
	*j = -1;
	redirection(data, data->flag->output);
	ft_free_n_null (data->flag->output);
	data->flag->output = NULL;
}

void	find_redir_in_same_array(t_vault *data, char *rl_dec_array,
	int line, int j)
{
	int	i;
	int	len;

	i = j;
	len = 0;
	len_of_redir(data, rl_dec_array, line);
	i = move_index_chevron2(data, line, i, rl_dec_array);
	i++;
	if (rl_dec_array[i] == data->flag->chevron)
		i++;
	while (rl_dec_array[i] == ' ')
		i++;
	if (rl_dec_array[i] == '\"' || rl_dec_array[i] == '\'')
	{
		data->quote->quote_priority = rl_dec_array[i];
		i++;
		while (rl_dec_array[i] != data->quote->quote_priority)
		{
			data->flag->output[len] = rl_dec_array[i];
			len++;
			i++;
		}
	}
	else
		end_of_redir(data, i, len, rl_dec_array);
}

int	move_index_chevron(t_vault *data, int line, int i, char *rl_dec_array)
{
	while (rl_dec_array[i])
	{
		if (rl_dec_array[i] == data->flag->chevron
			&& is_in_quote(data, line, i) == FALSE)
			break ;
		i++;
	}
	return (i);
}

int	move_index_chevron2(t_vault *data, int line, int i, char *rl_dec_array)
{
	while (rl_dec_array[i] != data->flag->chevron)
	{
		if (rl_dec_array[i + 1] == data->flag->chevron)
		{
			i++;
			while (is_in_quote(data, line, i) == TRUE)
				i++;
			i--;
		}
		i++;
	}
	return (i);
}

int	move_index_chevron3(t_vault *data, int i, int *len, char *rl_dec_array)
{
	data->quote->quote_priority = rl_dec_array[i];
	i++;
	(*len)++;
	while (rl_dec_array[i] != data->quote->quote_priority)
	{
		i++;
		(*len)++;
	}
	return (i);
}
