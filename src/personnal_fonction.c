/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   personnal_fonction.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbertin <mbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 12:15:09 by momo              #+#    #+#             */
/*   Updated: 2022/11/28 09:03:07 by mbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_double_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] && array[i][0])
	{
		printf("%s\n", array[i]);
		i++;
	}
}
