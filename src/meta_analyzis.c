/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_analyzis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbertin <mbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 10:05:10 by mbertin           #+#    #+#             */
/*   Updated: 2022/11/30 14:18:42 by mbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	meta_analyzis(t_vault *data)
{
	int	i;

	i = 0;
	data->quote_in->double_quote_count = 0;
	data->quote_in->simple_quote_count = 0;
	while (data->read_line[i])
	{
		if (data->read_line[i] == '\"')
			data->quote_in->double_quote_count++;
		else if (data->read_line[i] == '\'')
			data->quote_in->simple_quote_count++;
		i++;
	}
// savoir lequel vient en premier pour valider la paire
	if (data->quote_in->double_quote_count % 2 != 0)
		printf("Wrong argument\n");
	return (data->quote_in->double_quote_count);
}

// gérer commande "parametre">"output"
void	redirection_analysiz(t_vault *data)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (data->rl_decomp[i])
	{
		if (ft_strchr(data->rl_decomp[i], '>') != NULL
			&& check_if_inside_quote(data->rl_decomp[i], '>') != TRUE)
		{
			while (data->rl_decomp[i][j] && data->rl_decomp[i][j] != '>')
				j++;
			if (data->rl_decomp[i][j + 1] != '\0')
				data->output = output_to_redirect(data, i, j);
			else if (data->rl_decomp[i][j + 1] == '\0'
				&& data->rl_decomp[i + 1])
				data->output = ft_strdup(data->rl_decomp[i + 1]);
			else
				printf("alive: syntax error near unexpected token `newline'\n");
		}
		i++;
	}
}

// void	redirection(int output)
// {
// 	if (dup2(input, STDIN_FILENO) == -1)
// 	{
// 		write(2, "Error dup\n", 6);
// 		exit (1);
// 	}
// 	if (dup2(output, STDOUT_FILENO) == -1)
// 	{
// 		write(2, "Error dup\n", 10);
// 		exit (1);
// 	}
// }

char	*output_to_redirect(t_vault *data, int i, int j)
{
	char	*temp;
	int		len;
	int		temp_index;

	temp = NULL;
	temp_index = j;
	len = 0;
	j++;
	while (data->rl_decomp[i][temp_index])
	{
		len++;
		temp_index++;
	}
	temp = ft_calloc(sizeof(char), len + 1);
	temp_index = 0;
	while (data->rl_decomp[i][j])
	{
		temp[temp_index] = data->rl_decomp[i][j];
		j++;
		temp_index++;
	}
	return (temp);
}
