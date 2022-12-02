/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 21:05:24 by ewurstei          #+#    #+#             */
/*   Updated: 2022/12/02 14:38:55 by ewurstei         ###   ########.fr       */
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

// TODO Si on veut corriger le invalid read il faut changer la condition des boucles
//TODO J'ai remplacé dollar_var par temp pour pouvoir free temp à la ligne 87
void	find_var_value(t_vault *data, int row)
{
	int		j;
	int		k;
	int		len;
	char	*temp;

	j = 0;
	while (data->rl_decomp[row][j])
	{
		while (data->rl_decomp[row][j] && data->rl_decomp[row][j] != '$')
			j++;
		len = 0;
		k = j + 1;
		while (data->rl_decomp[row][k] != ' ' && data->rl_decomp[row][k]
			&& ft_char_env_var(data->rl_decomp[row][k]) == 1)
		{
			len++;
			k++;
		}
		temp = ft_substr(data->rl_decomp[row], j + 1, len);
		data->dollar_var = ft_strjoin(temp, "=");
		free (temp);
		k = 0;
		while (data->env[k])
		{
			if (ft_strnstr(data->env[k], data->dollar_var,
					ft_strlen(data->dollar_var)) == NULL)
				k++;
			else
			{
				expand_var(data, k, row, len);
				break ;
			}
		}
		j++;
	}
	if (data->dollar_var)
		free (data->dollar_var);
}

void	expand_var(t_vault *data, int row_var, int row, int len)
{
	int		len_var;
	int		i;
	int		j;
	int		k;
	int		use;
	char	*temp;

	use = 0;
	len_var = ft_strlen(data->env[row_var]) - len;
	temp = ft_calloc(sizeof(char),
			(ft_strlen(data->rl_decomp[row]) + len_var + 1));
	free (data->dollar_var);
	data->dollar_var = ft_substr(data->env[row_var], len + 1, len_var);
	j = 0;
	i = 0;
	while (data->rl_decomp[row][j])
	{
		k = 0;
		if (data->rl_decomp[row][j] == '$' && use != 1)
		{
			while (data->dollar_var[k])
			{
				temp[i] = data->dollar_var[k];
				k++;
				i++;
			}
			use = 1;
			j = j + len;
			free (data->dollar_var);
		}
		else
		{
			temp[i] = data->rl_decomp[row][j];
			i++;
		}
		j++;
	}
	free (data->rl_decomp[row]);
	data->rl_decomp[row] = ft_strdup(temp);
	free (temp);
	return ;
}

void	print_row(t_vault *data, int row)
{
	if (data->b_in->first_word == 1)
	{
		ft_putstr_fd(data->rl_decomp[row], 1);
		data->b_in->first_word = 0;
	}
	else
	{
		ft_putstr_fd(" ", 1);
		ft_putstr_fd(data->rl_decomp[row], 1);
	}
	return ;
}
