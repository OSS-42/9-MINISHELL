/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momo <momo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 15:41:57 by momo              #+#    #+#             */
/*   Updated: 2022/11/21 15:42:42 by momo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_strcmp(char *str, char *cmp)
{
	int	i;
	int	j;
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