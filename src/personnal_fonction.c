/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   personnal_fonction.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momo <momo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 12:15:09 by momo              #+#    #+#             */
/*   Updated: 2022/12/08 22:30:25 by momo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_double_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] && array[i][0] != '\0')
	{
		printf("%s\n", array[i]);
		i++;
	}
}

// La fonction ne vérifie pas si le char est avant ou apres les quotes.
int	check_if_inside_quote(char *str, char c)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			quote = str[i];
			i++;
			while (str[i] && str[i] != quote)
			{
				if (str[i] == c)
				{
					return (TRUE);
				}
				i++;
			}
		}
		i++;
	}
	return (FALSE);
}

