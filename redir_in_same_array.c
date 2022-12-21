/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in_same_array.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbertin <mbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 08:50:08 by mbertin           #+#    #+#             */
/*   Updated: 2022/12/21 13:33:20 by mbertin          ###   ########.fr       */
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
	}
	else if (c == '<' && data->tab_arg[i][*j + 1] == c)
	{
		data->tab_arg[i] = clean_the_chevron(data, data->tab_arg[i], 0, 0);
		find_redir_in_same_array(data, data->tab_arg[i]);
		heredoc(data);
	}
	else
		find_redir_in_same_array(data, data->tab_arg[i]);
	clean_redir(data, i);
	data->tab_arg[i] = clean_the_chevron(data, data->tab_arg[i], 0, 0);
	if (data->tab_arg[i][0] == '\0')
		find_decomposer_to_switch(data, i);
	*j = -1;
	if (data->flag->heredoc_delimiter == FALSE)
		redirection(data, data->flag->output);
	free (data->flag->output);
}

void	find_redir_in_same_array(t_vault *data, char *rl_decomp_array)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	len_of_redir(data, rl_decomp_array);
	while (rl_decomp_array[i] != data->flag->chevron)
		i++;
	i++;
	if (rl_decomp_array[i] == '\"' || rl_decomp_array[i] == '\'')
	{
		data->quote->quote_priority = rl_decomp_array[i];
		i++;
		while (rl_decomp_array[i] != data->quote->quote_priority)
		{
			data->flag->output[len] = rl_decomp_array[i];
			len++;
			i++;
		}
	}
	else
	{
		while (i < while_is_not_flag(rl_decomp_array, i))
			data->flag->output[len++] = rl_decomp_array[i++];
	}
}

void	len_of_redir(t_vault *data, char *rl_decomp_array)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (rl_decomp_array[i] != data->flag->chevron)
		i++;
	i++;
	if (rl_decomp_array[i] == '\"' || rl_decomp_array[i] == '\'')
	{
		data->quote->quote_priority = rl_decomp_array[i];
		i++;
		while (rl_decomp_array[i] != data->quote->quote_priority)
		{
			i++;
			len++;
		}
	}
	else
		len = while_is_not_flag(rl_decomp_array, i) - i;
	data->flag->output = ft_calloc(sizeof(char), len + 1);
}
