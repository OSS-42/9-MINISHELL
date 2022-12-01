/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 21:05:24 by ewurstei          #+#    #+#             */
/*   Updated: 2022/11/30 22:06:31 by ewurstei         ###   ########.fr       */
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
		else if (data->rl_decomp[row][j] == '$')
			data->dollar = 1;
		j++;			
	}
	return (data->b_in->echo_priority);
}

void	clean_quote(t_vault *data, int row)
{
	int	j;
	int	k;
	int	len;
	
	j = 0;
	k = 0;
	len = ft_strlen(data->rl_decomp[row]);
	data->b_in->echo_clean = ft_calloc(len + 1, sizeof(char));
	while (j < len)
	{
		if (data->rl_decomp[row][j] == data->b_in->echo_priority)
			j++;
		data->b_in->echo_clean[k] = data->rl_decomp[row][j];
		j++;
		k++;
	}
	free (data->rl_decomp[row]);
	data->rl_decomp[row] = ft_strdup(data->b_in->echo_clean);
	free (data->b_in->echo_clean);
}

void	find_var_value(t_vault *data, int row)
{
	int j;
	int k;
	int len;
	
	j = 0;
	while (data->rl_decomp[row][j])
	{
		if (data->rl_decomp[row][j] == '$')
		{
			len = 0;
			k = j;
			while (data->rl_decomp[row][k] != ' ' && data->rl_decomp[row][k] != '\0')
			{
				len++;
				k++;
			}
			data->dollar_var = ft_substr(data->rl_decomp[row], j + 1, len - 1);
			data->dollar_var = ft_strjoin(data->dollar_var, "=");
		}
		k = 0;
		while (data->env[k])
		{
			if (ft_strnstr(data->env[k], data->dollar_var, ft_strlen(data->dollar_var)) == NULL)
				k++;							
			else
				put_var_in_plain(data, k, row, len);
		}
		j++;
	}
}

void	put_var_in_plain(t_vault *data, int row_var, int row, int len)
{
	int		len_var;
	int		j;
	char	*temp;

	j = 0;
	len_var = ft_strlen(data->env[row_var]) - len;
	temp = ft_calloc(sizeof(char), (ft_strlen(data->rl_decomp[row]) + len_var + 1));
	free (data->dollar_var);
	data->dollar_var = ft_substr(data->env[row_var], len, len_var);
	while (data->rl_decomp[row][j])
	{
		if (data->rl_decomp[row][j] == '$')
		{
			if (j != 0)
				temp = ft_substr(data->rl_decomp[row], 0, j);
			data->rl_decomp[row] = ft_strjoin(temp, data->dollar_var);
			free (temp);
		}
		j++;
	}
	return ;
}

void	print_row(t_vault *data, int row)
{	
	if (data->b_in->first_word == 1)
	{
		ft_putstr_fd(data->rl_decomp[row], 1);
		data->b_in->first_word  = 0;
	}
	else
	{
		ft_putstr_fd(" ", 1);
		ft_putstr_fd(data->rl_decomp[row], 1);
	}
	data->b_in->echo_first = 0;
	data->b_in->echo_priority = 0;
	data->dollar = 0;
	return ;
}
