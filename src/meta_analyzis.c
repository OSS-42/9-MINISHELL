/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_analyzis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momo <momo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 10:05:10 by mbertin           #+#    #+#             */
/*   Updated: 2022/12/08 21:45:17 by momo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//TODO ajouter la verification de la premiere occurence VOIR AVEC ERIC
int		rl_prio_n_qty(t_vault *data)
{
	int		i;
	char	c;

	i = 0;
	c = '\0';
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

void	flag_count(t_vault *data)
{
	int	i;

	i = 0;
	while (data->rl_decomp[i] && data->rl_decomp[i][0])
	{
		if (ft_strchr(data->rl_decomp[i], '>') != NULL && check_if_inside_quote(data->rl_decomp[i], '>') == FALSE)
			data->flag->output_count++;
		if (ft_strchr(data->rl_decomp[i], '<') != NULL && check_if_inside_quote(data->rl_decomp[i], '<') == FALSE)
			data->flag->input_count++;
		if (ft_strchr(data->rl_decomp[i], '|') != NULL && check_if_inside_quote(data->rl_decomp[i], '|') == FALSE)
			data->flag->pipe_count++;
		i++;
	}
}

char	*output_to_redirect(t_vault *data, int i, int j)
{
	char	*temp;
	int		len;
	int		temp_index;

	temp = NULL;
	temp_index = j;
	len = 0;
	j++;
	while (data->rl_decomp[i][temp_index])
	{
		len++;
		temp_index++;
	}
	temp = ft_calloc(sizeof(char), len + 1);
	temp_index = 0;
	while (data->rl_decomp[i][j])
	{
		temp[temp_index] = data->rl_decomp[i][j];
		j++;
		temp_index++;
	}
	return (temp);
}

void	redirection_analysiz(t_vault *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->rl_decomp[i] && data->rl_decomp[i][0] != '\0')
	{
		data->flag->chevron_count = 0;
		j = 0;
		while(data->rl_decomp[i][j])
		{
			if (data->rl_decomp[i][j] == '>' && check_if_inside_quote(data->rl_decomp[i], '>') == FALSE)
				data->flag->chevron_count++;
			j++;
		}
		if (data->flag->chevron_count != 0)
		{
			data->flag->split_char = '>';
			split_on_char(data, i, data->flag->split_char);
			i = i + data->flag->chevron_count;
		}
		i++;
	}
}
