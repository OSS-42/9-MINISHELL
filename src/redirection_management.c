/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_management.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbertin <mbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 11:10:10 by mbertin           #+#    #+#             */
/*   Updated: 2022/12/09 08:57:49 by mbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	echo bonjour > test OK
	echo coucou> 1> 2> 3> 4 a continuer
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
	chevron ne contient rien d'autre. Enfin je m'est j = -1 car j'ai déplacé
	des éléments du tableau et donc je veux repasser dans la ligne actuel qui
	n'est plus la même. (à changer quand je testerais des cas qui ne
	décaleront pas le tableau)
*/
void	output_in_next_array(t_vault *data, int i, int *j, char c)
{
	int		begin;
	int		temp_count;
	int		len;
	char	*temp;

	begin = 0;
	len = 0;
	temp_count = 0;
	temp = NULL;
	find_output_in_next_array(data, data->rl_decomp[i + 1], c);
	if (*j == 0)
	{
		find_decomposer_to_switch(data, i);
		if (ft_strlen(data->rl_decomp[i]) == 1)
			find_decomposer_to_switch(data, i); // A changer pour s'assurer que je ne tombe pas sur ('"><|) en enlevant le output
		else
		{
			while (data->rl_decomp[i][begin] != '>')//Il va falloir que je créé un asset des caractere qui vont délimiter la fin du fichier ('"><|)
				begin++;
			temp_count = begin;
			while (data->rl_decomp[i][temp_count++])
				len++;
			temp = ft_substr(data->rl_decomp[i], begin, len);
			free (data->rl_decomp[i]);
			data->rl_decomp[i] = temp;
		}
	}
	else
	{
		data->rl_decomp[i][*j] = '\0';
		if (ft_strchr(data->rl_decomp[i + 1], c) != NULL
			&& check_if_inside_quote(data->rl_decomp[i + 1], c) == FALSE)//A changer pour s'assurer que je ne tombe pas sur ('"><|) en enlevant le output de l'array
		{
			while (data->rl_decomp[i + 1][begin] != '>')//Il va falloir que je créé un asset des caractere qui vont délimiter la fin du fichier ('"><|)
				begin++;
			temp_count = begin;
			while (data->rl_decomp[i + 1][temp_count++])
				len++;
			temp = ft_substr(data->rl_decomp[i + 1], begin, len);
			// free (data->rl_decomp[i + 1]);
			data->rl_decomp[i + 1] = temp;
		}
		else
			find_decomposer_to_switch(data, i + 1);
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
