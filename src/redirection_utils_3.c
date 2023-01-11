/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils_3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 18:26:46 by ewurstei          #+#    #+#             */
/*   Updated: 2023/01/11 12:02:04 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	clean_clean_redir(t_vault *data, int i)
{
	ft_free_n_null (data->tab_arg[i]);
	data->tab_arg[i] = ft_strdup(data->buffer);
	ft_free_n_null (data->buffer);
	data->buffer = NULL;
}
