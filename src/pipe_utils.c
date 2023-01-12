/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 10:15:12 by ewurstei          #+#    #+#             */
/*   Updated: 2023/01/12 11:18:25 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	create_tab_arg(t_vault *data, int row, int line)
{
	if (check_pipe_validity(data) == 1)
		return ;
	data->tab_arg = ft_calloc(sizeof(char *), (data->flag->pipe_count + 1) + 1);
	while (data->rl_dec[++row] && data->rl_dec[row] && data->rl_dec[row][0])
	{
		if (data->rl_dec[row][0] == '|')
		{
			if (data->rl_dec[row + 1] && data->rl_dec[row + 1][0] == '|')
			{
				data->rl_dec[row] = 0;
				data->flag->pipe_count = ft_dbl_ptr_len(data->tab_arg) - 1;
				return ;
			}
			if (!(data->rl_dec[++row]))
			{
				data->flag->pipe_count = ft_dbl_ptr_len(data->tab_arg) - 1;
				return ;
			}
			line++;
		}
		data->buffer = ft_strdup(data->rl_dec[row]);
		if (data->buffer[0] != '\0')
			switch_lines(data, row, line);
	}
	ft_dbl_ptr_free((void **)data->rl_dec);
}

void	switch_lines(t_vault *data, int row, int line)
{
	char	*temp;

	temp = NULL;
	if (data->tab_arg[line] == NULL)
	{
		data->tab_arg[line] = ft_strdup(data->buffer);
		ft_free_n_null (data->buffer);
		data->buffer = NULL;
		if (data->rl_dec[row + 1] && data->rl_dec[row + 1][0])
			validate_the_switch(data, row, line);
	}
	else
	{
		temp = ft_strjoin(data->tab_arg[line], data->buffer);
		ft_free_n_null (data->buffer);
		data->buffer = NULL;
		ft_free_n_null (data->tab_arg[line]);
		data->tab_arg[line] = ft_strdup(temp);
		ft_free_n_null (temp);
		if (data->rl_dec[row + 1] && data->rl_dec[row + 1][0])
			validate_the_switch(data, row, line);
	}
}

void	do_the_switch(t_vault *data, int line)
{
	data->buffer = ft_strjoin(data->tab_arg[line], " ");
	ft_free_n_null (data->tab_arg[line]);
	data->tab_arg[line] = ft_strdup(data->buffer);
	ft_free_n_null (data->buffer);
	data->buffer = NULL;
}

void	validate_the_switch(t_vault *data, int row, int line)
{
	if (ft_strchr(data->rl_dec[row + 1], '|') != 0
		&& ft_strlen((const char *) data->rl_dec[row + 1]) == 1)
		return ;
	do_the_switch(data, line);
}

int	check_pipe_validity(t_vault *data)
{
	if (data->rl_dec[0][0] == '|')
	{
		ft_dbl_ptr_free((void **)data->rl_dec);
		return (1);
	}
	return (0);
}
