/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in_same_array_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 11:43:05 by mbertin           #+#    #+#             */
/*   Updated: 2023/01/09 17:01:07 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	clean_redir(t_vault *data, int i)
{
	int		len;
	int		temp;
	int		begin;

	len = 0;
	begin = 0;
	temp = 0;
	len = len_without_redir(data, i, temp, &begin);
	data->buffer = ft_calloc(sizeof(char), len + 1);
	if (begin != 0)
	{
		data->buffer[temp] = data->flag->chevron;
		temp++;
		if (data->tab_arg[i][begin] == ' ')
			begin++;
		while (data->tab_arg[i][begin] && data->tab_arg[i][begin] != '\0')
		{
			data->buffer[temp] = data->tab_arg[i][begin];
			temp++;
			begin++;
		}
	}
	else
		data->buffer = clean_redir_from_zero(data, i, data->buffer, begin);
	free (data->tab_arg[i]);
	data->tab_arg[i] = ft_strdup(data->buffer);
	free (data->buffer);
}

char	*clean_redir_from_zero(t_vault *data, int i, char *str, int begin)
{
	int	temp;

	temp = 0;
	while (data->tab_arg[i][begin] && data->tab_arg[i][begin] != '\0')
	{
		temp = while_not_chevron(data, i, str, &begin);
		while (data->tab_arg[i][begin] == ' ')
			begin++;
		if (data->tab_arg[i][begin] == '\"' || data->tab_arg[i][begin] == '\'')
			begin = while_quote(data, data->tab_arg[i], begin);
		else
		{
			while (data->tab_arg[i][begin] == ' ')
			{
				str[temp] = data->tab_arg[i][begin];
				temp++;
				begin++;
			}
			begin = while_is_not_flag(data->tab_arg[i], begin);
		}
		if (data->tab_arg[i][begin])
		{
			while (data->tab_arg[i][begin] && data->tab_arg[i][begin] != '\0')
			{
				str[temp] = data->tab_arg[i][begin];
				temp++;
				begin++;
			}
		}
	}
	return (str);
}

int	while_not_chevron(t_vault *data, int i, char *str, int *begin)
{
	int	temp;

	temp = 0;
	while (data->tab_arg[i][*begin])
	{
		if (data->tab_arg[i][*begin] == data->flag->chevron
			&& is_in_quote(data, i, *begin) == FALSE)
			break ;
		str[temp] = data->tab_arg[i][*begin];
		temp++;
		(*begin)++;
	}
	str[temp] = data->tab_arg[i][*begin];
	temp++;
	(*begin)++;
	return (temp);
}

int	len_without_redir(t_vault *data, int i, int temp, int *begin)
{
	int	len;

	len = 0;
	if (data->tab_arg[i][0] == data->flag->chevron)
		len = len_from_chevron_at_zero(data, i, begin);
	else
	{
		while (data->tab_arg[i][temp])
		{
			if (data->tab_arg[i][temp] == data->flag->chevron
				&& is_in_quote(data, i, temp) == FALSE)
				break ;
			temp++;
		}
		len = temp;
		if (data->tab_arg[i][temp])
			len = return_len(data, i, &temp, len);
	}
	return (len);
}

int	len_from_chevron_at_zero(t_vault *data, int i, int *begin)
{
	int	temp;
	int	len;

	temp = 1;
	len = 1;
	while (data->tab_arg[i][temp] == ' ')
		temp++;
	if (data->tab_arg[i][temp] == '\'' || data->tab_arg[i][temp] == '\"')
		temp = while_quote(data, data->tab_arg[i], temp);
	else
	{
		while (data->tab_arg[i][temp] && (data->tab_arg[i][temp] != '>'
		&& data->tab_arg[i][temp] != '<' && data->tab_arg[i][temp] != ' '))
			temp++;
	}
	*begin = temp;
	if (data->tab_arg[i][temp])
	{
		while (data->tab_arg[i][temp])
		{
			temp++;
			len++;
		}
	}
	return (len);
}
