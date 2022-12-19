/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momo <momo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 08:53:07 by mbertin           #+#    #+#             */
/*   Updated: 2022/12/18 19:44:28 by momo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*clean_the_chevron(t_vault *data, char *str)
{
	char	*temp;
	int		clean;
	int		i;
	int		j;

	i = 0;
	j = 0;
	clean = 0;
	temp = ft_calloc(sizeof(char), ft_strlen(str));
	if (!temp)
	{
		free (temp);
		exit (EXIT_FAILURE);
	}
	while (str[i] && str[i] != '\0')
	{
		if (str[i] == data->flag->chevron && clean == 0)
		{
			clean = 1;
			i++;
		}
		if (str[i])
		{
			temp[j] = str[i];
			i++;
			j++;
		}
	}
	free (str);
	return (temp);
}

// Ajouter une sécurité pour m'assurer que le flag n'Est pas entre quote
int	flag_in_str(char *str)
{
	if (ft_strchr(str, '>') != NULL || ft_strchr(str, '<') != NULL
		|| ft_strchr(str, '|') != NULL)
		return (TRUE);
	return (FALSE);
}

int	while_is_not_flag(char *str, int i)
{
	while (str[i] && str[i] != '|' && str[i] != '>' && str[i] != '<')
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

void	dup_from_begin(t_vault *data, int decomp_i, int j, char *temp)
{
	while (data->rl_decomp[decomp_i][data->begin]
		&& data->rl_decomp[decomp_i][data->begin] != '\0')
	{
		temp[j] = data->rl_decomp[decomp_i][data->begin];
		data->begin++;
		j++;
	}
	data->begin = 0;
	free (data->rl_decomp[decomp_i]);
	data->rl_decomp[decomp_i] = temp;
}
