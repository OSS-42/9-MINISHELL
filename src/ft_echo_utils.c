/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 21:05:24 by ewurstei          #+#    #+#             */
/*   Updated: 2022/12/09 00:23:08 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//TODO Si on veut corriger le invalid R il faut changer la condition des boucles
//TODO J'ai remplacé dollar_var par temp pour pouvoir free temp à la ligne 87

//attention : si la var n'existe pas, echo ne doit rien afficher
char	*var_extract(t_vault *data, int row, int position)
{
	int		k;
	char	*temp;

	temp = NULL;
	k = position + 1;
	while (data->rl_decomp[row][k]
		&& ft_char_env_var(data->rl_decomp[row][k] == 1))
	{
		data->dollar_var_len++;
		k++;
	}
	if (data->dollar_var_len > 0)
	{
		temp = ft_substr(data->rl_decomp[row], position + 1,
				data->dollar_var_len);
		data->dollar_var = ft_strjoin(temp, "=");
		free (temp);
	}
	temp = does_var_exist(data, row);
	return (temp);
}

char	*does_var_exist(t_vault *data, int row)
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
			break ;
		}
		i++;
	}
	temp = expand_var(data, i, row);
	return (temp);
}

char	*expand_var(t_vault *data, int row_var, int row)
{
	int		len_var;
	char	*temp;

	temp = NULL;
	if (data->flag->var_not_found == 1)
	{
		temp = ft_calloc(sizeof(char), 2);
		temp = " ";
		return (temp);
	}
	else
	{
		len_var = ft_strlen(data->env[row_var]) - data->dollar_var_len;
		temp = ft_calloc(sizeof(char),
				(ft_strlen(data->rl_decomp[row]) + len_var + 3));
		temp = ft_substr(data->env[row_var],
				data->dollar_var_len + 1, len_var);
	}
	return (temp);
}

// void	var_to_value(t_vault *data, int row, char *temp)
// {
// 	int		i;
// 	int		j;

// 	j = 0;
// 	i = 0;
// 	while (data->rl_decomp[row][j])
// 	{
// 		if (data->rl_decomp[row][j] == '$' && data->flag->runs != 1)
// 		{
// 			i = copy_var(temp, data->dollar_var, i);
// 			data->flag->runs = 1;
// 			j = j + data->dollar_var_len;
// 			free (data->dollar_var);
// 		}
// 		else
// 		{
// 			temp[i] = data->rl_decomp[row][j];
// 			i++;
// 		}
// 		j++;
// 	}
// }

// int	copy_var(char *dest, char *source, int pos)
// {
// 	int		k;

// 	k = 0;
// 	while (source[k])
// 	{
// 		dest[pos] = source[k];
// 		k++;
// 		pos++;
// 	}
// 	return (pos);
// }