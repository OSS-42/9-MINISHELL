/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_management.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbertin <mbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 11:10:10 by mbertin           #+#    #+#             */
/*   Updated: 2022/12/19 11:09:48 by mbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
echo test 1 > test > test1 > test2
echo test 2 >1 >2 >3
echo test 3> test> test1> test2
echo test 4>test>test1>test2
echo test 5>1 > 2> 3 >4 > 5
echo "test 6">"test" > "test1"
echo "test 7">"test" >"test1"
echo "test 8">"test"> "test1"> "test2"
echo "test 9">"test">"test1">"test2"
echo "test 10" > "test"> "test1" >"test2">"test3"> "test4"
echo "test 11" >test 4
echo test 12 > "tes>t"
echo test 13 > "tes>t">test1
echo test 14 > 1> 2
echo test 15 >"tes>t">test1
echo test 16>"tes>t">test1

	echo 1' '2" "3 Segfault si double execution

*/

/*
	Je vais chercher un chevon qui n'est pas entre quote et le nom du
	fichier qui suit. Si le nom du fichier est dans le prochain array de
	rl_decomp je rentre dans output_in_next_array.

	A partir du moment ou le fichier est trouvé et que la redirection est
	faite, je vais supprimer le chevron et le nom du fichier qui suit.
*/
void	execute_redirection(t_vault *data, int i, int j)
{
	data->flag->stdout_backup = dup(STDOUT_FILENO);
	data->flag->stdin_backup = dup(STDIN_FILENO);
	while (data->rl_decomp[i] && data->rl_decomp[i][0])
	{
		if ((ft_strchr(data->rl_decomp[i], '>') != NULL
				&& check_if_inside_quote(data->rl_decomp[i], '>') == FALSE)
			|| (ft_strchr(data->rl_decomp[i], '<') != NULL
				&& check_if_inside_quote(data->rl_decomp[i], '<') == FALSE))
		{
			while (data->rl_decomp[i][j])
			{
				if ((data->rl_decomp[i][j] == '>'
					|| data->rl_decomp[i][j] == '<')
					&& !data->rl_decomp[i][j + 1])
					redir_in_next_array(data, i, &j, data->rl_decomp[i][j]);
				else if (data->rl_decomp[i][j] == '>'
				|| data->rl_decomp[i][j] == '<')
					redir_in_same_array(data, i, &j, data->rl_decomp[i][j]);
				j++;
			}
		}
		j = 0;
		i++;
	}
}

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
	find_redir_in_next_array(data, data->rl_decomp[i + 1]);
	if (*j == 0)
	{
		clean_redir_next_array(data, i + 1);
		if (ft_strlen(data->rl_decomp[i]) == 1)
			find_decomposer_to_switch(data, i);
		else
			data->rl_decomp[i] = clean_the_chevron(data, data->rl_decomp[i]);
		if (ft_strlen(data->rl_decomp[i]) < 1)
			find_decomposer_to_switch(data, i);
	}
	else
	{
		data->rl_decomp[i][*j] = '\0';
		if (flag_in_str(data->rl_decomp[i + 1]) == FALSE)
			find_decomposer_to_switch(data, i + 1);
		else
			clean_redir_next_array(data, i + 1);
	}
	stdout_redirection(data, data->flag->output);
	*j = -1;
}

void	redir_in_same_array(t_vault *data, int i, int *j, char c)
{
	data->flag->chevron = c;
	find_redir_in_same_array(data, data->rl_decomp[i]);
	clean_redir(data, i);
	data->rl_decomp[i] = clean_the_chevron(data, data->rl_decomp[i]);
	if (data->rl_decomp[i][0] == '\0')
		find_decomposer_to_switch(data, i);
	*j = -1;
	stdout_redirection(data, data->flag->output);
}

void	stdout_redirection(t_vault *data, char *redirection)
{
	int	fd;

	fd = 0;
	if (data->flag->chevron == '>')
	{
		fd = open(redirection, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			printf("Probleme avec open sur fd_out\n");
		}
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			printf("Probleme avec dup2 sur fd_out\n");
		}
	}
	else if (data->flag->chevron == '<')
	{
		fd = open(redirection, O_RDONLY);
		if (fd == -1)
		{
			printf("Probleme avec open sur fd_out\n");
		}
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			printf("Probleme avec dup2 sur fd_out\n");
		}
	}
	free (redirection);
}
