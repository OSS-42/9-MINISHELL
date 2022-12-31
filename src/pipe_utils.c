/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momo <momo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 10:15:12 by ewurstei          #+#    #+#             */
/*   Updated: 2022/12/31 10:18:11 by momo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	create_tab_arg(t_vault *data, int row, int line)
{
	data->tab_arg = ft_calloc(sizeof(char *), (data->flag->pipe_count + 1) + 1);
	while (data->rl_dec[++row] && data->rl_dec[row]
		&& data->rl_dec[row][0])
	{
		if (data->rl_dec[row][0] == '|')
		{
			if (!(data->rl_dec[row][1]))
			{
				line++;
				row++;
				if (!(data->rl_dec[row]))
					return ;
			}
			else if (data->rl_dec[row][1] == '|')
			{
				data->rl_dec[row] = NULL;
				return ;
			}
		}
		data->buffer = ft_strdup(data->rl_dec[row]);
		if (data->buffer[0] != '\0')
			switch_lines(data, row, line);
	}
}

void	switch_lines(t_vault *data, int row, int line)
{
	char	*temp;

	temp = NULL;
	// printf("rl_dec\n");
	// print_double_array(data->rl_dec);
	if (data->tab_arg[line] == NULL)
	{
		data->tab_arg[line] = ft_strdup(data->buffer);
		free (data->buffer);
		// if (data->rl_dec[row + 1] && data->rl_dec[row + 1][0]
		// 	&& data->rl_dec[row + 1][1])
		// 	do_the_switch(data, line);
		if (data->rl_dec[row + 1] && data->rl_dec[row + 1][0])
			do_the_switch(data, line);
	}
	else
	{
		temp = ft_strjoin(data->tab_arg[line], data->buffer);
		free (data->buffer);
		free (data->tab_arg[line]);
		data->tab_arg[line] = ft_strdup(temp);
		free (temp);
		if (data->rl_dec[row + 1] && data->rl_dec[row + 1][0])
		{
			if (ft_strchr(data->rl_dec[row + 1], '|') != 0
				&& ft_strlen((const char *) data->rl_dec[row + 1]) == 1)
				return ;
			do_the_switch(data, line);
		}
	}
}

void	do_the_switch(t_vault *data, int line)
{
	data->buffer = ft_strjoin(data->tab_arg[line], " ");
	free (data->tab_arg[line]);
	data->tab_arg[line] = ft_strdup(data->buffer);
	free (data->buffer);
}
