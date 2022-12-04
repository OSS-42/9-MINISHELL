/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_analyzis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momo <momo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 10:05:10 by mbertin           #+#    #+#             */
/*   Updated: 2022/12/04 10:22:07 by momo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//TODO ajouter la verification de la premiere occurence VOIR AVEC ERIC
void	meta_analyzis(t_vault *data)
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
	if (data->quote_in->double_quote_count % 2 != 0
		|| data->quote_in->simple_quote_count % 2 != 0)
		printf("Wrong argument\n");
}

void	flag_count(t_vault *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->rl_decomp[i] && data->rl_decomp[i][0])
	{
		if (ft_strchr(data->rl_decomp[i], '>') != NULL && check_if_inside_quote(data->rl_decomp[i], '>') == FALSE)
			data->flag->output_count++;
		if (ft_strchr(data->rl_decomp[i], '<') != NULL && check_if_inside_quote(data->rl_decomp[i], '<') == FALSE)
			data->flag->input_count++;
		if (ft_strchr(data->rl_decomp[i], '|') != NULL && check_if_inside_quote(data->rl_decomp[i], '|') == FALSE)
			data->flag->pipe_count++;
		j = 0;
		while (data->rl_decomp[i][j])
		{
			if (data->rl_decomp[i][j] == '$')
				data->flag->dollar_count++;
			j++;
		}
		i++;
	}
}

// commande parametre > fichier
// < fichier commande parametre > fichier
void	redirection_analysiz(t_vault *data)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (data->rl_decomp[i] && data->rl_decomp[i][0] != '\0')
	{
		if (ft_strchr(data->rl_decomp[i], '>') != NULL
			&& check_if_inside_quote(data->rl_decomp[i], '>') != TRUE)
		{
			while (data->rl_decomp[i][j] && data->rl_decomp[i][j] != '>')
				j++;
			if (data->rl_decomp[i][j + 1] != '\0')
				data->flag->output = output_to_redirect(data, i, j);
			else if (data->rl_decomp[i][j + 1] == '\0'
				&& data->rl_decomp[i + 1])
			{
				i++;
				data->flag->output = ft_strdup(data->rl_decomp[i]);
				data->quote_in->spc_count = 1;
				find_decomposer_to_switch(data, i);
			}
			else
				printf("alive: syntax error near unexpected token `newline'\n");
		}
		i++;
	}
}

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