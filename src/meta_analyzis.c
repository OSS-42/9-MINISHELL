/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_analyzis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbertin <mbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 10:05:10 by mbertin           #+#    #+#             */
/*   Updated: 2022/12/08 11:06:04 by mbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//TODO ajouter la verification de la premiere occurence VOIR AVEC ERIC
int		rl_prio_n_qty(t_vault *data)
{
	int		i;
	char	c;

	i = 0;
	c = '\0';
	while (data->read_line[i])
	{
		if (data->read_line[i] == '\"' || data->read_line[i] == '\'')
		{
			c = data->read_line[i];
			if (c == '\"')
				data->quote->double_quote_count++;
			else if (c == '\'')
				data->quote->simple_quote_count++;
			i++;
			while (data->read_line[i] && data->read_line[i] != c)
				i++;
			if (!data->read_line[i])
			{
				printf("Wrong argument\n");
				return (FALSE);
			}
			else if (c == '\"')
				data->quote->double_quote_count++;
			else if (c == '\'')
				data->quote->simple_quote_count++;
		}
		i++;
	}
	return (TRUE);
}

void	flag_count(t_vault *data)
{
	int	i;
//	int	j;

	i = 0;
	while (data->rl_decomp[i] && data->rl_decomp[i][0])
	{
		if (ft_strchr(data->rl_decomp[i], '>') != NULL && check_if_inside_quote(data->rl_decomp[i], '>') == FALSE)
			data->flag->output_count++;
		if (ft_strchr(data->rl_decomp[i], '<') != NULL && check_if_inside_quote(data->rl_decomp[i], '<') == FALSE)
			data->flag->input_count++;
		if (ft_strchr(data->rl_decomp[i], '|') != NULL && check_if_inside_quote(data->rl_decomp[i], '|') == FALSE)
			data->flag->pipe_count++;
		i++;
	}
}

// A faire :
//echo 'bonjour'>'test'
//echo bonjour >test>test1
//echo bonjour >test >test1> test2

//Fait :
// echo bonjour>test
// echo bonjour >test
// echo bonjour> test> test1> test2
// echo bonjour > test > test1 > test2
// echo bonjour > test1> test2 > test3> test4

/*
	C'est pas un probleme d'avoir des chevrons collé et du coup ne plus savoir si c'est un happend ou une redirection. L'important c'est de savoir le quel à était appelé en dernier
	car c'est dans celui-ci que j'écrirais le contenu et que je s'aurais si il s'agit d'un tronc ou d'un happend. Donc créé un flag de priorité.
*/

//echo bonjour>file
// void	redirection_analysiz(t_vault *data)
// {
// 	int		i;
// 	int		j;
// 	int		k;
// 	int		len;

// 	i = 0;
// 	j = 0;
// 	k = 0;
// 	data->flag->output = ft_calloc(sizeof(char *), data->flag->output_count + 1);
// 	while (data->rl_decomp[i] && data->rl_decomp[i][0] != '\0')
// 	{
// 		if (ft_strchr(data->rl_decomp[i], '>') != NULL
// 			&& check_if_inside_quote(data->rl_decomp[i], '>') != TRUE)
// 		{
// 			while (data->rl_decomp[i][j] && data->rl_decomp[i][j] != '>')
// 				j++;
// 			if (data->rl_decomp[i][j + 1] != '\0')
// 			{
// 				data->flag->output[k] = output_to_redirect(data, i, j);
// 				data->rl_decomp[i][j + 1] = '\0';
// 				k++;
// 			}
// 			else if (data->rl_decomp[i][j + 1] == '\0' && data->rl_decomp[i + 1])
// 			{
// 				if (ft_strchr(data->rl_decomp[i + 1], '>') == NULL)
// 				{
// 					data->flag->output[k] = ft_strdup(data->rl_decomp[i + 1]);
// 					data->spc_count++;
// 					find_decomposer_to_switch(data, i + 1);
// 					k++;
// 				}
// 				else
// 				{
// 					data->flag->output[k] = ft_strdup(data->rl_decomp[i + 1]);
// 					len = ft_strlen(data->flag->output[k]);
// 					if (data->flag->output[k][len - 1] == '>'
// 					&& check_if_inside_quote(data->rl_decomp[i], '>') != TRUE)
// 					{
// 						data->flag->output[k][len - 1] = '\0';
// 						free (data->rl_decomp[i + 1]);
// 						data->rl_decomp[i + 1] = ft_strdup(">\0");
// 					}
// 					k++;
// 				}
// 			}
// 			else
// 				printf("alive: syntax error near unexpected token `newline'\n");
// 		}
// 		i++;
// 	}
// 	data->spc_count = 0;
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

void	redirection_analysiz(t_vault *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->rl_decomp[i] && data->rl_decomp[i][0] != '\0')
	{
		data->flag->chevron_count = 0;
		j = 0;
		while(data->rl_decomp[i][j])
		{
			if (data->rl_decomp[i][j] == '>' && check_if_inside_quote(data->rl_decomp[i], '>') == FALSE)
				data->flag->chevron_count++;
			j++;
		}
		if (data->flag->chevron_count != 0)
		{
			data->flag->split_char = '>';
			split_on_char(data, i, data->flag->split_char);
			i = i + data->flag->chevron_count;
		}
		i++;
	}
}
