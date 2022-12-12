/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_management.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbertin <mbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 11:10:10 by mbertin           #+#    #+#             */
/*   Updated: 2022/12/12 14:24:22 by mbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	echo bonjour > test > test1 > test2 OK
	echo bonjour> test> test1> test2 OK
	echo coucou >1 >2 >3 OK
	echo coucou>test>test1>test2 OK
	echo coucou>1 > 2> 3 >4 > 5 OK
*/

/*
	Je vais chercher un chevon qui n'est pas entre quote et le nom du
	fichier qui suit. Si le nom du fichier est dans le prochain array de
	rl_decomp je rentre dans output_in_next_array.

	A partir du moment ou le fichier est trouvé et que la redirection est
	faite, je vais supprimer le chevron et le nom du fichier qui suit.
*/
void	execute_redirection(t_vault *data)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	data->flag->stdout_backup = dup(STDOUT_FILENO);
	while (data->rl_decomp[i] && data->rl_decomp[i][0])
	{
		if (ft_strchr(data->rl_decomp[i], '>') != NULL
			&& check_if_inside_quote(data->rl_decomp[i], '>') == FALSE)
		{
			while (data->rl_decomp[i][j])
			{
				if (data->rl_decomp[i][j] == '>' && !data->rl_decomp[i][j + 1])
					output_in_next_array(data, i, &j, '>');
				else if (data->rl_decomp[i][j] == '>')
					output_in_same_array(data, i, &j, '>');
				j++;
			}
		}
		j = 0;
		i++;
	}
}


void	output_in_same_array(t_vault *data, int i, int *j, char c)
{
	(void)c;
	(void)j;
	find_output_in_same_array(data, data->rl_decomp[i], '>');
	clean_output(data, i, 0);
	data->rl_decomp[i] = clean_the_chevron(data->rl_decomp[i]);
	// Ajouter une condition : find_decomposer_to_switch(data, i);
	*j = -1;
	stdout_redirection(data->flag->output);
}

void	find_output_in_same_array(t_vault *data, char *rl_decomp_array, char c)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (rl_decomp_array[i] != c)
		i++;
	i++;
	len = while_is_not_flag(rl_decomp_array, i) - i;
	data->flag->output = ft_calloc(sizeof(char), len);
	len = 0;
	while (i < while_is_not_flag(rl_decomp_array, i))
	{
		data->flag->output[len] = rl_decomp_array[i];
		len++;
		i++;
	}
}

void	clean_output_next_array(t_vault *data, int i)
{
	int		j;
	int		len;
	char	*temp;

	len = 0;
	j = while_is_not_flag(data->rl_decomp[i], 0);
	temp = NULL;
	while (data->rl_decomp[i][j])
	{
		j++;
		len++;
	}
	temp = ft_calloc(sizeof(char), len + 1);
	j = while_is_not_flag(data->rl_decomp[i], 0);
	len = 0;
	while (data->rl_decomp[i][j])
	{
		temp[len] = data->rl_decomp[i][j];
		j++;
		len++;
	}
	free (data->rl_decomp[i]);
	data->rl_decomp[i] = temp;
}

void	clean_output(t_vault *data, int i, int j)
{
	int		len;
	int		temp;
	char	*str;
	int		clean;

	len = 0;
	temp = j;
	str = NULL;
	clean = 0;
	while (data->rl_decomp[i][temp] && data->rl_decomp[i][temp] != '>')
	{
		temp++;
		len++;
	}
	if (data->rl_decomp[i][temp] == '>')
	{
		temp++;
		len++;
	}
	temp = while_is_not_flag(data->rl_decomp[i], temp);
	while (data->rl_decomp[i][temp])
	{
		temp++;
		len++;
	}
	str = ft_calloc(sizeof(char), len + 1);
	temp = 0;
	while (data->rl_decomp[i][j])
	{
		if (data->rl_decomp[i][j] == '>' && clean == 0)
		{
			str[temp] = data->rl_decomp[i][j];
			j++;
			temp++;
			j = while_is_not_flag(data->rl_decomp[i], j);
			str[temp] = data->rl_decomp[i][j];
			j++;
			temp++;
			clean = 1;
		}
		else
		{
			str[temp] = data->rl_decomp[i][j];
			temp++;
			j++;
		}
	}
	free (data->rl_decomp[i]);
	data->rl_decomp[i] = str;
}

int	while_is_not_flag(char *str, int i)
{
	while (str[i] && str[i] != '\'' && str[i] != '\"' && str[i] != '|'
		&& str[i] != '>' && str[i] != '<')
		i++;
	return (i);
}

// Ajouter une sécurité pour m'assurer que le flag n'Est pas entre quote
int	flag_in_str(char *str)
{
	if (ft_strchr(str, '\'') != NULL || ft_strchr(str, '\"') != NULL
		|| ft_strchr(str, '>') != NULL || ft_strchr(str, '<') != NULL
		|| ft_strchr(str, '|') != NULL)
		return (TRUE);
	return(FALSE);
}

/*
	Je vais chercher le nom du output dans le prochain array.
	Quand je l'ai trouvé, si l'array en question ne contient que l'output
	je décalle d'un rang le tableau. Même chose si l'array ou ce trouve le
	chevron ne contient rien d'autre. Enfin je m'est j = -1 car si j'ai déplacé
	des éléments du tableau et donc je veux repasser dans la ligne actuel qui
	n'est plus la même.
*/
void	output_in_next_array(t_vault *data, int i, int *j, char c)
{
	find_output_in_next_array(data, data->rl_decomp[i + 1], c);
	if (*j == 0)
	{
		clean_output_next_array(data, i + 1);
		if (ft_strlen(data->rl_decomp[i]) == 1)
			find_decomposer_to_switch(data, i);
		else
			data->rl_decomp[i] = clean_the_chevron(data->rl_decomp[i]);
	}
	else
	{
		data->rl_decomp[i][*j] = '\0';
		if (flag_in_str(data->rl_decomp[i + 1]) == FALSE) // Ajouter une sécurité pour m'assurer que le flag n'Est pas entre guillemets
			find_decomposer_to_switch(data, i + 1);
		else
			clean_output_next_array(data, i + 1);
	}
	stdout_redirection(data->flag->output);
	*j = -1;
}

void	find_output_in_next_array(t_vault *data, char *rl_decomp_array, char c)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (rl_decomp_array[i] && rl_decomp_array[i] != c
		&& rl_decomp_array[i] != '|')
	{
		i++;
		len++;
	}
	i = 0;
	data->flag->output = ft_substr(rl_decomp_array, i, len);
}

char	*clean_the_chevron(char *str)
{
	char	*temp;
	int		clean;
	int		i;
	int		j;

	i = 0;
	j = 0;
	clean = 0;
	temp = ft_calloc(sizeof(char), ft_strlen(str));
	while (str[i])
	{
		if (str[i] == '>' && clean == 0)
		{
			clean = 1;
			i++;
		}
		if (str[i])
			temp[j] = str[i];
		i++;
		j++;
	}
	free (str);
	return (temp);
}

void	stdout_redirection(char *redirection)
{
	int	fd;

	fd = 0;
	fd = open(redirection, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		printf("Probleme avec open sur fd_out\n");
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		printf("Probleme avec dup2 sur fd_out\n");
	}
	free (redirection);
}

/*
	Dans le cas ou la case qui contient > ce trouve dans un string qui contient
	d'autre éléments cette fonction va retirer le > de cette string.
*/
// char	*clean_the_chevron(char *str)
// {
// 	int		begin;
// 	int		temp_count;
// 	int		len;
// 	char	*temp;

// 	begin = 0;
// 	len = 0;
// 	while (str[begin] != '>' && str[begin] != '<' && str[begin] != '|'
// 		&& str[begin] != '\'' && str[begin] != '\"')
// 		begin++;
// 	if (begin == 0)
// 		begin++;
// 	temp_count = begin;
// 	while (str[temp_count++])
// 		len++;
// 	temp = ft_substr(str, begin, len);
// 	free (str);
// 	return (temp);
// }

// void	output_in_same_array(t_vault *data, int i, int *j, char c)
// {
// 	(void)c;
// 	(void)j;
// 	data->rl_decomp[i] = clean_the_chevron(data->rl_decomp[i]);
// 	if (flag_in_str(data->rl_decomp[i]) == TRUE)
// 	{
// 		*j = while_is_not_flag(data->rl_decomp[i], *j);
// 		data->flag->output = ft_substr(data->rl_decomp[i], 0, *j);
// 		clean_output(data, i, *j);
// 	}
// 	else
// 	{
// 		data->flag->output = ft_substr(data->rl_decomp[i], 0, ft_strlen(data->rl_decomp[i]));
// 		find_decomposer_to_switch(data, i);
// 	}
// 	*j = -1;
// 	stdout_redirection(data->flag->output);
// }
