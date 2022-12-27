/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 10:15:12 by ewurstei          #+#    #+#             */
/*   Updated: 2022/12/27 00:02:43 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//retourner un code d'erreur.
void	create_tab_arg(t_vault *data, int row, int line)
{
	data->tab_arg = ft_calloc(sizeof(char *), (data->flag->pipe_count + 1) + 1);
	while (data->rl_decomp[++row] && data->rl_decomp[row]
		&& data->rl_decomp[row][0])
	{
		if (data->rl_decomp[row][0] == '|')
		{
			if (!(data->rl_decomp[row][1]))
			{
				line++;
				row++;
				if (!(data->rl_decomp[row]))
					return ;
			}
			else if (data->rl_decomp[row][1] == '|')
			{
				data->rl_decomp[row] = NULL;
				return ;
			}
		}
		data->buffer = ft_strdup(data->rl_decomp[row]);
		if (data->buffer[0] != '\0')
			switch_lines(data, row, line);
	}
}

void	switch_lines(t_vault *data, int row, int line)
{
	char	*buffer;

	buffer = NULL;
	if (data->tab_arg[line] == NULL)
	{
		data->tab_arg[line] = ft_strdup(data->buffer);
		free (data->buffer);
		if (data->rl_decomp[row + 1] && data->rl_decomp[row + 1][0]
			&& data->rl_decomp[row + 1][1])
			data->tab_arg[line] = ft_strjoin(data->tab_arg[line], " ");
	}
	else
	{
		buffer = ft_strjoin(data->tab_arg[line], data->buffer);
		free (data->buffer);
		free (data->tab_arg[line]);
		data->tab_arg[line] = ft_strdup(buffer);
		free (buffer);
		if (data->rl_decomp[row + 1] && data->rl_decomp[row + 1][0]
			&& data->rl_decomp[row + 1][1])
			data->tab_arg[line] = ft_strjoin(data->tab_arg[line], " ");
	}
}

// void	clear_pipe_from_str(t_vault *data, int line)
// {
// 	char	*buffer;

// 	buffer = NULL;
// 	if (data->tab_arg[line] == NULL)
// 	{
// 		data->tab_arg[line] = ft_strdup(data->buffer);
// 		free (data->buffer);
// 		data->buffer = ft_calloc(sizeof(char), 500);
// 	}
// 	else
// 	{
// 		buffer = ft_strjoin(data->tab_arg[line], data->buffer);
// 		free (data->buffer);
// 		free (data->tab_arg[line]);
// 		data->tab_arg[line] = ft_strdup(buffer);
// 		free (buffer);
// 		data->buffer = ft_calloc(sizeof(char), 500);
// 	}
// }

// int	parsing_pipe(t_vault *data, int row, int line)
// {
// 	int	i;
// 	int	j;

// 	i = -1;
// 	j = 0;
// 	data->buffer = ft_calloc(sizeof(char), 500);
// 	while (data->rl_decomp[row] && data->rl_decomp[row][++i])
// 	{
// 		if (data->rl_decomp[row][i] == '|')
// 		{
// 			clear_pipe_from_str(data, line);
// 			line++;
// 			j = 0;
// 		}
// 		else
// 			copy_in_temp(data, row, i, &j);
// 	}
// 	return (line);
// }

// void	copy_in_temp(t_vault *data, int row, int i, int *j)
// {
// 	data->buffer[*j] = data->rl_decomp[row][i];
// 	(*j)++;
// }
