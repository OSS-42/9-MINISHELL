/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in_same_array.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momo <momo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 08:50:08 by mbertin           #+#    #+#             */
/*   Updated: 2022/12/31 16:45:44 by momo             ###   ########.fr       */
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
		find_redir_in_same_array(data, data->tab_arg[i], i);

	}
	else if (c == '<' && data->tab_arg[i][*j + 1] == c)
	{
		data->tab_arg[i] = clean_the_chevron(data, data->tab_arg[i], 0, 0);
		find_redir_in_same_array(data, data->tab_arg[i], i);
		heredoc(data);
	}
	else
		find_redir_in_same_array(data, data->tab_arg[i], i);
	clean_redir(data, i);
	data->tab_arg[i] = clean_the_chevron(data, data->tab_arg[i], 0, 0);
	*j = -1;
	redirection(data, data->flag->output);
	free (data->flag->output);
}

void	find_redir_in_same_array(t_vault *data, char *rl_dec_array, int line)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	len_of_redir(data, rl_dec_array);
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
	{
		while (rl_dec_array[i] && rl_dec_array[i] != ' '
			&& rl_dec_array[i] != '<' && rl_dec_array[i]
			!= '>' && rl_dec_array[i] != '|')
			data->flag->output[len++] = rl_dec_array[i++];
	}
}

void	len_of_redir(t_vault *data, char *rl_dec_array)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (rl_dec_array[i] != data->flag->chevron)
		i++;
	i++;
	while (rl_dec_array[i] == ' ')
		i++;
	if (rl_dec_array[i] == '\"' || rl_dec_array[i] == '\'')
	{
		data->quote->quote_priority = rl_dec_array[i];
		i++;
		len++;
		while (rl_dec_array[i] != data->quote->quote_priority)
		{
			i++;
			len++;
		}
	}
	else
		len = while_is_not_flag(rl_dec_array, i) - i;
	data->flag->output = ft_calloc(sizeof(char), len + 1);
}
