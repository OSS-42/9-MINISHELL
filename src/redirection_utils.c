/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbertin <mbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 08:53:07 by mbertin           #+#    #+#             */
/*   Updated: 2023/01/05 09:51:32 by mbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*clean_the_chevron(t_vault *data, char *str, int line, int i)
{
	char	*temp;
	int		clean;
	int		j;
	int		len; //debug

	clean = 0;
	j = 0;
	len = ft_strlen(str);// debug
	// temp = ft_calloc(sizeof(char), ft_strlen(str) + 1);
	temp = ft_calloc(sizeof(char), len + 1); //debug
	if (!temp)
	{
		free (temp);
		error_message(data, "unexpected error", "1\0");
		exit (EXIT_FAILURE);
	}
	while (str[i] && str[i] != '\0')
	{
		if (str[i] == data->flag->chevron
			&& is_in_quote(data, line, i) == FALSE && clean == 0)
		{
			clean = 1;
			i++;
			while (str[i] && str[i] == ' ')
				i++;
		}
		else if (str[i])
			temp[j++] = str[i++];
	}
	if (j != 0 && temp[j - 1] == ' ')
		temp[j - 1] = '\0';
	free (str);
	return (temp);
}

int	flag_in_str(char *str)
{
	if (ft_strchr(str, '>') != NULL || ft_strchr(str, '<') != NULL
		|| ft_strchr(str, '|') != NULL)
		return (TRUE);
	return (FALSE);
}

int	while_is_not_flag(char *str, int i)
{
	while (str[i] && str[i] != '|' && str[i] != '>'
		&& str[i] != '<' && str[i] != ' ')
		i++;
	return (i);
}

int	len_in_quote(t_vault *data, char *str, int *i)
{
	int	len;

	len = 0;
	data->quote->quote_priority = str[*i];
	(*i)++;
	while (str[*i] != data->quote->quote_priority)
	{
		(*i)++;
		len++;
	}
	return (len);
}

int	while_quote(t_vault *data, char *str, int i)
{
	data->quote->quote_priority = str[i];
	i++;
	while (str[i] != data->quote->quote_priority)
		i++;
	i++;
	return (i);
}
