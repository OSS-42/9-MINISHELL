/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dbl_ptr_copy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbertin <mbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 10:20:38 by ewurstei          #+#    #+#             */
/*   Updated: 2023/01/10 15:48:47 by mbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char **ft_dbl_ptr_copy(char **source)
{
	int		row;
	char	**temp;

	row = 0;
	temp = NULL;
	if (!source)
		return (NULL);
	temp = ft_calloc(sizeof(char *), ft_dbl_ptr_len(source) + 1);
	while (source[row])
	{
		temp[row] = ft_strdup(source[row]);
		row++;
	}
	return (temp);
}
