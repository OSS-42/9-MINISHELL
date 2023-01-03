/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 08:53:07 by mbertin           #+#    #+#             */
/*   Updated: 2023/01/02 23:29:38 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Ajouter des free et message d'erreur au exit
char	*clean_the_chevron(t_vault *data, char *str, int line, int i)
{
	char	*temp;
	int		clean;
	int		j;

	clean = 0;
	j = 0;
	temp = ft_calloc(sizeof(char), ft_strlen(str));
	if (!temp)
	{
		free (temp);
		error_message(data, "unexpected error", "1\0");
		exit (EXIT_FAILURE);
	}
	while (str[i] && str[i] != '\0')
	{
		if (str[i] == data->flag->chevron && is_in_quote(data, line, i) == FALSE && clean == 0)
		{
			clean = 1;
			i++;
			while (str[i] == ' ')
				i++;
		}
		else if (str[i])
			temp[j++] = str[i++];
	}
	if (temp[j - 1] == ' ')
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
	while (str[i] && str[i] != '|' && str[i] != '>' && str[i] != '<' && str[i] != ' ')
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
