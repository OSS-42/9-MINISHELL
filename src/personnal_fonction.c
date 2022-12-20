/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   personnal_fonction.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbertin <mbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 12:15:09 by momo              #+#    #+#             */
/*   Updated: 2022/12/20 09:29:47 by mbertin          ###   ########.fr       */
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

// Changer la fonction pour qu'elle renvoie FALSE si le char c ce trouve
//	en dehors des quotes puis à l'intérieur des quotes. EX : echo coucou >"tes>t">test1
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

