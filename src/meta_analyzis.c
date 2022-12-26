/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_analyzis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 10:05:10 by mbertin           #+#    #+#             */
/*   Updated: 2022/12/26 11:34:14 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//TODO ajouter la verification de la premiere occurence VOIR AVEC ERIC
int	rl_prio_n_qty(t_vault *data, int i, char c)
{
	while (data->read_line[i])
	{
		if (data->read_line[i] == '\"' || data->read_line[i] == '\'')
		{
			c = data->read_line[i];
			if (c == '\"')
				data->quote->double_quote_count++;
			else if (c == '\'')
				data->quote->simple_quote_count++;
			i++;
			while (data->read_line[i] && data->read_line[i] != c)
				i++;
			if (!data->read_line[i])
			{
				printf("Wrong argument\n");
				return (FALSE);
			}
			else if (c == '\"')
				data->quote->double_quote_count++;
			else if (c == '\'')
				data->quote->simple_quote_count++;
		}
		i++;
	}
	return (TRUE);
}

void	flag_count(t_vault *data, int i, int j)
{
	char	c;

	c = '\0';
	while (data->rl_decomp[i] && data->rl_decomp[i][0])
	{
		while (data->rl_decomp[i][j])
		{
			if (data->rl_decomp[i][j] == '\'' || data->rl_decomp[i][j] == '\"')
			{
				c = data->rl_decomp[i][j];
				j++;
				while (data->rl_decomp[i][j] != c)
				{
					if (data->rl_decomp[i][j] == '|')
						if (data->rl_decomp[i][j + 1] == c && data->rl_decomp[i][j - 1] == c)
							data->flag->pipe_count++;
					j++;
				}
			}
			if (data->rl_decomp[i][j] == '>')
				data->flag->output_count++;
			if (data->rl_decomp[i][j] == '<')
				data->flag->input_count++;
			if (data->rl_decomp[i][j] == '|')
				data->flag->pipe_count++;
			j++;
		}
		j = 0;
		i++;
	}
}
