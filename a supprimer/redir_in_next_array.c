/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in_next_array.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 08:45:42 by mbertin           #+#    #+#             */
/*   Updated: 2023/01/08 12:04:52 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	Je vais chercher le nom du output dans le prochain array.
	Quand je l'ai trouvé, si l'array en question ne contient que l'output
	je décalle d'un rang le tableau. Même chose si l'array ou ce trouve le
	chevron ne contient rien d'autre. Enfin je m'est j = -1 car si j'ai déplacé
	des éléments du tableau et donc je veux repasser dans la ligne actuel qui
	n'est plus la même.
*/
void	redir_in_next_array(t_vault *data, int i, int *j, char c)
{
	data->flag->chevron = c;
	if (c == '>' && data->tab_arg[i][*j + 1] == c)
	{
		data->flag->append = TRUE;
		data->tab_arg[i] = clean_the_chevron(data, data->tab_arg[i], 0, 0);
		find_redir_in_next_array(data, data->tab_arg[i + 1]);
	}
	else if (c == '<' && data->tab_arg[i][*j + 1] == c)
	{
		data->tab_arg[i] = clean_the_chevron(data, data->tab_arg[i], 0, 0);
		find_redir_in_next_array(data, data->tab_arg[i + 1]);
		heredoc(data, i);
	}
	else
		find_redir_in_next_array(data, data->tab_arg[i + 1]);
	redir_in_next_array_interlude(data, j, i);
	// if (*j == 0)
	// {
	// 	clean_redir_next_array(data, i + 1);
	// 	if (ft_strlen(data->tab_arg[i]) == 1)
	// 	{
	// 		find_decomposer_to_switch(data, i);
	// 		if (ft_strlen(data->tab_arg[i]) == 0)
	// 			find_decomposer_to_switch(data, i);
	// 	}
	// 	else
	// 	{
	// 		data->tab_arg[i]
	// 			= clean_the_chevron(data, data->tab_arg[i], 0, 0);
	// 		if (ft_strlen(data->tab_arg[i]) < 1)
	// 			find_decomposer_to_switch(data, i);
	// 	}
	// }
	// else
	// {
	// 	data->tab_arg[i][*j] = '\0';
	// 	if (flag_in_str(data->tab_arg[i + 1]) == FALSE)
	// 		find_decomposer_to_switch(data, i + 1);
	// 	else
	// 		clean_redir_next_array(data, i + 1);
	// }
	if (data->flag->heredoc == FALSE)
		redirection(data, data->flag->output);
	free (data->flag->output);
	*j = -1;
}

void	find_redir_in_next_array(t_vault *data, char *rl_dec_array)
{
	int		j;
	int		len;

	j = 0;
	len = 0;
	if (rl_dec_array[j] == '\"' || rl_dec_array[j] == '\'')
	{
		data->quote->quote_priority = rl_dec_array[j];
		j++;
		while (rl_dec_array[j] != data->quote->quote_priority)
		{
			j++;
			len++;
		}
		j = 1;
	}
	else
		len = while_is_not_flag(rl_dec_array, j);
	data->flag->output = ft_substr(rl_dec_array, j, len);
}

void	clean_redir_next_array(t_vault *data, int i)
{
	int		j;
	int		len;
	int		begin;

	len = 0;
	j = 0;
	if (data->tab_arg[i][j] == '\'' || data->tab_arg[i][j] == '\"')
		j = while_quote(data, data->tab_arg[i], j);
	else
		j = while_is_not_flag(data->tab_arg[i], 0);
	begin = j;
	while (data->tab_arg[i][j])
	{
		j++;
		len++;
	}
	token_without_redir_name(data, i, begin, len);
}

void	token_without_redir_name(t_vault *data, int i, int begin, int len)
{
	int		j;
	char	*temp;

	j = 0;
	temp = ft_calloc(sizeof(char), len + 1);
	while (data->tab_arg[i][begin])
	{
		temp[j] = data->tab_arg[i][begin];
		begin++;
		j++;
	}
	free (data->tab_arg[i]);
	data->tab_arg[i] = temp;
}

void	redir_in_next_array_interlude(t_vault *data, int *j, int i)
{
	if (*j == 0)
	{
		clean_redir_next_array(data, i + 1);
		if (ft_strlen(data->tab_arg[i]) == 1)
		{
			find_decomposer_to_switch(data, i);
			if (ft_strlen(data->tab_arg[i]) == 0)
				find_decomposer_to_switch(data, i);
		}
		else
		{
			data->tab_arg[i]
				= clean_the_chevron(data, data->tab_arg[i], 0, 0);
			if (ft_strlen(data->tab_arg[i]) < 1)
				find_decomposer_to_switch(data, i);
		}
	}
	else
	{
		data->tab_arg[i][*j] = '\0';
		if (flag_in_str(data->tab_arg[i + 1]) == FALSE)
			find_decomposer_to_switch(data, i + 1);
		else
			clean_redir_next_array(data, i + 1);
	}
}