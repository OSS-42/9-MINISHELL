/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   personnal_fonction.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbertin <mbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 12:15:09 by momo              #+#    #+#             */
/*   Updated: 2022/12/01 16:17:20 by mbertin          ###   ########.fr       */
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
			while (str[i] != quote)
			{
				if (str[i] == c)
				{
					// printf("%c est dans des quotes\n", c);
					return (TRUE);
				}
				i++;
			}
		}
		i++;
	}
	// printf("%c n'est pas dans des quotes\n", c);
	return (FALSE);
}
