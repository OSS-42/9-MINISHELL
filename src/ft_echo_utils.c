/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 21:05:24 by ewurstei          #+#    #+#             */
/*   Updated: 2022/12/16 11:16:52 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//TODO Si on veut corriger le invalid R il faut changer la condition des boucles
//TODO J'ai remplacé dollar_var par temp pour pouvoir free temp à la ligne 87

int	check_next_char(t_vault *data, int row, int i)
{
	if (data->rl_decomp[row][i + 1] == '\''
		|| data->rl_decomp[row][i + 1] == '\"')
	{
		i = i - 2;
		while (data->rl_decomp[row][i])
		{
			if (data->rl_decomp[row][i] != '\''
				|| data->rl_decomp[row][i] != '\"'
					|| data->rl_decomp[row][i] != '$')
				i++;
			data->buffer[data->pos] = data->rl_decomp[row][i];
			data->pos++;
			i++;
		}
	}
	return (i);
}

int	dollar_var_to_extract(t_vault *data, int row, int i)
{
	char	*temp;
	int		k;

	if (ft_char_env_var(data->rl_decomp[row][i + 1]) != 1)
	{
		i = check_next_char(data, row, i);
		return (i);
	}
	temp = var_extract(data, row, i + 1);
	k = 0;
	while (temp[k])
	{
		data->buffer[data->pos] = temp[k];
		data->pos++;
		k++;
	}
	if (data->flag->var_not_found == 1)
		return (0);
	free (temp);
	return (0);
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
			break ;
		}
		i++;
	}
	free (temp);
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

void	echo_minus(t_vault *data)
{
	int		row;
	int		line;
	int		i;
	char	**temp_swap;

	row = 0;
	i = 0;
	while (data->rl_decomp[row] && data->rl_decomp[row][i])
	{
//		printf("row : %d = %s\n", row, data->rl_decomp[row]);
//		printf("priority : %d\n", data->b_in->echo_priority);
		while (data->rl_decomp[row][i] == '-' && data->rl_decomp[row][i])
			i++;
		if (i > 1)
		{
			data->b_in->echo_forget_minus = 1;
			return ;
		}
		else if (data->b_in->echo_priority != 0)
		{
			while (data->rl_decomp[row][i])
			{
				if (data->rl_decomp[row][i] != 'n')
				{
					data->b_in->echo_forget_minus = 1;
					data->b_in->dont_do_minus = 1;
					break ;
				}
				else
					data->b_in->echo_forget_minus = 0;
				i++;
			}
		}
		else
		{
			while (data->rl_decomp[row][i] && data->rl_decomp[row][i] != ' ')
			{
				if (data->rl_decomp[row][i] != 'n')
				{
					data->b_in->echo_forget_minus = 1;
					break ;
				}
				else
					data->b_in->echo_forget_minus = 0;
				i++;
			}
		}
//		printf("%d\n", data->b_in->echo_forget_minus);
		if (data->b_in->echo_forget_minus == 0 && data->rl_decomp[row + 1])
		{
			temp_swap = ft_calloc(sizeof(char *), ft_dbl_ptr_len(data->rl_decomp));
			i = 0;
			line = 0;
			while (data->rl_decomp[line])
			{
				if (line == row)
					line++;
				if (data->rl_decomp[line])
					temp_swap[i] = ft_strdup(data->rl_decomp[line]);
				else
				{
					temp_swap[i] = NULL;
					break ;
				}
				line++;
				i++;
			}
//			print_double_array(temp_swap);
			ft_dbl_ptr_realloc(data->rl_decomp, ft_dbl_ptr_len(temp_swap));
			i = 0;
			while (temp_swap[i])
			{
				free (data->rl_decomp[i]);
				data->rl_decomp[i] = ft_strdup(temp_swap[i]);
				free (temp_swap[i]);
				i++;
			}
			data->rl_decomp[i] = NULL;
//			print_double_array(data->rl_decomp);
			free (temp_swap);
			data->b_in->echo_flag_n = 1;
			data->b_in->echo_minus_n = 1;
//			printf("row : %d = %s\n", row, data->rl_decomp[row]);
			row = row - 1;
//			printf("row : %d = %s\n", row, data->rl_decomp[row]);
		}
		row++;
		i = 0;
	}
	// if (data->rl_decomp[row + 1] == NULL)
	// 	data->b_in->echo_flag_n = 0;
}

//en erreur : echo "-n salut bonjour"
//en erreur : echo -nnnn -nnnn salut bonjour
