/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_management.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbertin <mbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 11:10:10 by mbertin           #+#    #+#             */
/*   Updated: 2022/12/08 16:27:12 by mbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	echo bonjour > test OK
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

void	output_in_next_array(t_vault *data, int i, int *j, char c)
{
	find_output_in_next_array(data, data->rl_decomp[i + 1], c);
	if (*j == 0)
		find_decomposer_to_switch(data, i);
	find_decomposer_to_switch(data, i);
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
