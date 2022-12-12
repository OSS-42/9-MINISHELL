/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 21:05:24 by ewurstei          #+#    #+#             */
/*   Updated: 2022/12/11 23:00:45 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//TODO Si on veut corriger le invalid R il faut changer la condition des boucles
//TODO J'ai remplacé dollar_var par temp pour pouvoir free temp à la ligne 87

//attention : si la var n'existe pas, echo ne doit rien afficher

void	dollar_var_to_extract(t_vault *data, int row, int i)
{
	char	*temp;
	int		k;

	temp = var_extract(data, row, i + 1);
	k = 0;
	while (temp[k])
	{
		data->buffer[data->pos] = temp[k];
		data->pos++;
		k++;
	}
	free (temp);
}

char	*var_extract(t_vault *data, int row, int position)
{
	int		k;
	char	*temp;

	temp = NULL;
	k = position;
	data->dollar_var_len = 0;
	while (data->rl_decomp[row][k]
		&& ft_char_env_var(data->rl_decomp[row][k]) == 1)
	{
		data->dollar_var_len++;
		k++;
	}
	if (data->dollar_var_len > 0)
	{
		temp = ft_substr(data->rl_decomp[row], position,
				data->dollar_var_len);
		data->dollar_var = ft_strjoin(temp, "=");
		free (temp);
	}
	else
		return (NULL);
	temp = does_var_exist(data);
	return (temp);
}

char	*does_var_exist(t_vault *data)
{
	int		i;
	char	*temp;

	i = 0;
	temp = ft_calloc(sizeof(char), 500);
	while (data->env[i])
	{
		if (ft_strnstr(data->env[i], data->dollar_var,
				ft_strlen(data->dollar_var) + 1) == NULL)
			data->flag->var_not_found = 1;
		else
		{
			data->flag->var_not_found = 0;
			free (temp);
			break ;
		}
		i++;
	}
	temp = expand_var(data, i);
	return (temp);
}

char	*expand_var(t_vault *data, int row_var)
{
	int		len_var;
	char	*temp;

	temp = NULL;
	if (data->flag->var_not_found == 1)
	{
		temp = ft_calloc(sizeof(char), 2);
		temp = " \0";
		free (data->dollar_var);
		return (temp);
	}
	else
	{
		len_var = ft_strlen(data->env[row_var]) - data->dollar_var_len;
		temp = ft_substr(data->env[row_var],
				data->dollar_var_len + 1, len_var);
		free (data->dollar_var);
	}
	return (temp);
}
