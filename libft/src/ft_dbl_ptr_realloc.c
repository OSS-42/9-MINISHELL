/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dbl_ptr_realloc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 21:18:04 by ewurstei          #+#    #+#             */
/*   Updated: 2022/12/01 21:36:04 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	**ft_dbl_ptr_realloc(char **tab, int size)
{
	if (tab)
		free_dbl_ptr((void **)tab);
	tab = ft_calloc(size, sizeof(char *));
	return (tab);
}
