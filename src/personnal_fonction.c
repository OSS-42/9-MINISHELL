/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   personnal_fonction.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momo <momo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 12:15:09 by momo              #+#    #+#             */
/*   Updated: 2022/12/31 16:10:10 by momo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_double_array(char **array)
{
	int	row;

	row = 0;
	while (array[row] && array[row][0])
	{
		printf("ligne #%d : %s\n", row, array[row]);
		row++;
	}
	printf("\n");
}

int	check_if_inside_quote(char *str, char c)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (FALSE);
		else if (str[i] == '\"' || str[i] == '\'')
		{
			quote = str[i];
			i++;
			while (str[i] && str[i] != quote)
				i++;
		}
		i++;
	}
	return (TRUE);
}

