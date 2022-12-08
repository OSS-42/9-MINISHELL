/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_management.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbertin <mbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 11:10:10 by mbertin           #+#    #+#             */
/*   Updated: 2022/12/08 15:31:07 by mbertin          ###   ########.fr       */
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
				{
					data->flag->output = output_in_next_array(data,
							data->rl_decomp[i + 1], '>', i);
					if (!data->rl_decomp[i][j - 1])
						find_decomposer_to_switch(data, i);
					find_decomposer_to_switch(data, i);
					do_redirection(data->flag->output);
					j = -1;
				}
				j++;
			}
		}
		j = 0;
		i++;
	}
}

char	*output_in_next_array(t_vault *data, char *rl_decomp_array,
	char c, int rl_decomp_index)
{
	int		i;
	char	*output;
	int		len;

	i = 0;
	len = 0;
	output = NULL;
	(void)rl_decomp_index;
	(void)data;
	while (rl_decomp_array[i] && rl_decomp_array[i] != c
		&& rl_decomp_array[i] != '|')
	{
		i++;
		len++;
	}
	i = 0;
	output = ft_substr(rl_decomp_array, i, len);
	// if (rl_decomp_array[len] == '\0')
	// {
	// 	data->spc_count = 1;
	// 	find_decomposer_to_switch(data, rl_decomp_index);
	// }
	return (output);
}

void	do_redirection(char *redirection)
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
}
