/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbertin <mbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 08:53:07 by mbertin           #+#    #+#             */
/*   Updated: 2022/12/15 11:58:05 by mbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*clean_the_chevron(char *str)
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
		if (str[i] == '>' && clean == 0)
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
