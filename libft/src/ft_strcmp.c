/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbertin <mbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 15:41:57 by momo              #+#    #+#             */
/*   Updated: 2022/11/22 08:43:33 by mbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_strcmp(char *str, char *cmp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
		i++;
	while (cmp[j])
		j++;
	if (j != i)
		return (0);
	while (i >= 0)
	{
		if (str[i] != cmp[j])
			return (0);
		i--;
		j--;
	}
	return (1);
}