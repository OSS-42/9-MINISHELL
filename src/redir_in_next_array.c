/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in_next_array.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbertin <mbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 08:45:42 by mbertin           #+#    #+#             */
/*   Updated: 2022/12/19 10:05:15 by mbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	find_redir_in_next_array(t_vault *data, char *rl_decomp_array)
{
	int		j;
	int		len;

	j = 0;
	len = 0;
	if (rl_decomp_array[j] == '\"' || rl_decomp_array[j] == '\'')
	{
		data->quote->quote_priority = rl_decomp_array[j];
		j++;
		while (rl_decomp_array[j] != data->quote->quote_priority)
		{
			j++;
			len++;
		}
		j = 1;
	}
	else
		len = while_is_not_flag(rl_decomp_array, j);
	data->flag->output = ft_substr(rl_decomp_array, j, len);
}

void	clean_redir_next_array(t_vault *data, int i)
{
	int		j;
	int		len;
	int		begin;

	len = 0;
	j = 0;
	if (data->rl_decomp[i][j] == '\'' || data->rl_decomp[i][j] == '\"')
		j = while_quote(data, data->rl_decomp[i], j);
	else
		j = while_is_not_flag(data->rl_decomp[i], 0);
	begin = j;
	while (data->rl_decomp[i][j])
	{
		j++;
		len++;
	}
	token_without_redir_name(data, i, begin, len);
}

void	token_without_redir_name(t_vault *data, int i, int begin, int len)
{
	int		j;
	char	*temp;

	j = 0;
	temp = ft_calloc(sizeof(char), len + 1);
	while (data->rl_decomp[i][begin])
	{
		temp[j] = data->rl_decomp[i][begin];
		begin++;
		j++;
	}
	free (data->rl_decomp[i]);
	data->rl_decomp[i] = temp;
}