/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dbl_ptr_realloc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 21:18:04 by ewurstei          #+#    #+#             */
/*   Updated: 2022/12/06 21:32:19 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

//	if (tab)
//		free_dbl_ptr((void **)tab);

char	**ft_dbl_ptr_realloc(char **tab, int size)
{
	tab = ft_calloc(size, sizeof(char *));
	return (tab);
}
