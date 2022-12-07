/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbertin <mbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 21:05:24 by ewurstei          #+#    #+#             */
/*   Updated: 2022/12/07 09:25:42 by mbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	quote_priority(t_vault *data, int row)
{
	int	j;

	j = 0;
	while (data->rl_decomp[row][j])
	{
		if (data->rl_decomp[row][j] == '\"')
		{
			data->b_in->echo_dble_q++;
			if (data->b_in->echo_first == 0)
				data->b_in->echo_first = 2;
			if (data->b_in->echo_dble_q % 2 == 0 && data->b_in->echo_first == 2)
				data->b_in->echo_priority = 34;
		}
		else if (data->rl_decomp[row][j] == '\'')
		{
			data->b_in->echo_sgle_q++;
			if (data->b_in->echo_first == 0)
				data->b_in->echo_first = 1;
			if (data->b_in->echo_sgle_q % 2 == 0 && data->b_in->echo_first == 1)
				data->b_in->echo_priority = 39;
		}
		j++;
	}
	return (data->b_in->echo_priority);
}

void	clean_quote(t_vault *data, int row)
{
	int		j;
	int		k;
	int		len;
	char	*temp;

	j = 0;
	k = 0;
	len = ft_strlen(data->rl_decomp[row]);
	temp = ft_calloc(len, sizeof(char));
	while (j < len)
	{
		if (data->rl_decomp[row][j] == data->b_in->echo_priority)
			j++;
		temp[k] = data->rl_decomp[row][j];
		j++;
		k++;
	}
	free (data->rl_decomp[row]);
	data->rl_decomp[row] = temp;
}

//TODO Si on veut corriger le invalid R il faut changer la condition des boucles
//TODO J'ai remplacé dollar_var par temp pour pouvoir free temp à la ligne 87

//attention : si la var n'existe pas, echo ne doit rien afficher
void	find_var_value(t_vault *data, int row)
{
	int	j;
	int	k;

	j = -1;
	while (data->rl_decomp[row][++j])
	{
		while (data->rl_decomp[row][j] && data->rl_decomp[row][j] != '$')
			j++;
		var_extract(data, row, j);
		k = 0;
		while (data->env[k])
		{
			if (ft_strnstr(data->env[k], data->dollar_var,
					ft_strlen(data->dollar_var)) == NULL)
				k++;
			else
			{
				expand_var(data, k, row);
				break ;
			}
		}
	}
	free(data->dollar_var);
}

void	var_extract(t_vault *data, int row, int position)
{
	int		k;
	char	*temp;

	k = position + 1;
	while (data->rl_decomp[row][k] && data->rl_decomp[row][k] != ' '
		&& ft_char_env_var(data->rl_decomp[row][k]) == 1)
	{
		data->dollar_var_len++;
		k++;
	}
	temp = ft_substr(data->rl_decomp[row], position + 1, data->dollar_var_len);
	data->dollar_var = ft_strjoin(temp, "=");
	free (temp);
	return ;
}

void	expand_var(t_vault *data, int row_var, int row)
{
	int		len_var;
	char	*temp;

	len_var = ft_strlen(data->env[row_var]) - data->dollar_var_len;
	temp = ft_calloc(sizeof(char),
			(ft_strlen(data->rl_decomp[row]) + len_var + 2));
	free (data->dollar_var);
	data->dollar_var = ft_substr(data->env[row_var],
			data->dollar_var_len + 1, len_var);
	var_to_value(data, row, temp);
	free (data->rl_decomp[row]);
	data->rl_decomp[row] = ft_strdup(temp);
	free (temp);
	return ;
}


