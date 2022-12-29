/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in_same_array_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbertin <mbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 11:43:05 by mbertin           #+#    #+#             */
/*   Updated: 2022/12/29 11:16:27 by mbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	clean_redir(t_vault *data, int i)
{
	int		len;
	int		temp;
	int		begin;
	char	*str;

	len = 0;
	begin = 0;
	temp = 0;
	len = len_without_redir(data, i, temp, &begin);
	str = ft_calloc(sizeof(char), len + 1);
	if (begin != 0)
	{
		str[temp] = data->flag->chevron;
		temp++;
		if (data->tab_arg[i][begin] == ' ')
			begin++;
		while (data->tab_arg[i][begin] && data->tab_arg[i][begin] != '\0')
		{
			str[temp] = data->tab_arg[i][begin];
			temp++;
			begin++;
		}
	}
	else
		str = clean_redir_from_zero(data, i, str, begin);
	free (data->tab_arg[i]);
	data->tab_arg[i] = str;
}

char	*clean_redir_from_zero(t_vault *data, int i, char *str, int begin)
{
	int	temp;

	temp = 0;
	while (data->tab_arg[i][begin] && data->tab_arg[i][begin] != '\0')
	{
		temp = while_not_chevron(data, i, str, &begin);
		if (data->tab_arg[i][begin] == '\"'
			|| data->tab_arg[i][begin] == '\'')
			begin = while_quote(data, data->tab_arg[i], begin);
		else
			begin = while_is_not_flag(data->tab_arg[i], begin);
		if (data->tab_arg[i][begin])
		{
			while (data->tab_arg[i][begin]
				&& data->tab_arg[i][begin] != '\0')
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
	while (data->tab_arg[i][*begin] != data->flag->chevron)
	{
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
		temp = while_is_not_flag(data->tab_arg[i], temp);
		len = temp;
		if (data->tab_arg[i][temp])
		{
			temp++;
			len++;
			temp = while_is_not_flag(data->tab_arg[i], temp);
			len++;
			while (data->tab_arg[i][temp])
			{
				temp++;
				len++;
			}
		}
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
