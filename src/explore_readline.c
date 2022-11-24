/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   explore_readline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbertin <mbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:55:29 by momo              #+#    #+#             */
/*   Updated: 2022/11/24 14:56:43 by mbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	explore_readline(t_vault *data)
{
	data->readline_decomposer = ft_split(data->read_line, ' ');
	find_str_doublequote(data);
	print_double_array(data->readline_decomposer);
	// reduce_space(data);
	built_in(data);
}

void	built_in(t_vault *data)
{
	if (ft_strcmp("cd", data->readline_decomposer[0]) == 1)
		ft_cd(data);
	if (ft_strcmp("pwd", data->readline_decomposer[0]) == 1)
		ft_pwd(data);
	if (ft_strcmp("echo", data->readline_decomposer[0]) == 1)
		ft_echo(data);
	if (ft_strcmp("exit", data->readline_decomposer[0]) == 1)
		ft_exit (0);
}

void	find_str_doublequote(t_vault *data)
{
	int		i;
	int		begin;
	int		len;

	i = 0;
	begin = 0;
	len = 1;
	while (data->read_line[i])
	{
		if (data->read_line[i] == '\"')
		{
			begin = i;
			i++;
			while (data->read_line[i] != '\"')
			{
				len++;
				i++;
			}
			len++;
			replace_decomposer_array(data, len, begin, i);
		}
		i++;
	}
}

void	replace_decomposer_array(t_vault *data, int len, int begin, int end)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (data->readline_decomposer[i])
	{
		while (data->readline_decomposer[i][j])
		{
			if (data->readline_decomposer[i][j] == '\"')
			{
				free(data->readline_decomposer[i]);
				data->readline_decomposer[i] = ft_calloc(sizeof(char), len + 1);
				j = 0;
				while (begin <= end)
				{
					data->readline_decomposer[i][j] = data->read_line[begin];
					begin++;
					j++;
				}
				i++;
				find_decomposer_to_switch(data, i);
				return ;
			}
			j++;
		}
		j = 0;
		i++;
	}
}

void	find_decomposer_to_switch(t_vault *data, int to_switch)
{
	int	i;
	int	j;

	i = to_switch;
	j = 0;
	while (data->readline_decomposer[i])
	{
		while (data->readline_decomposer[i][j])
		{
			if (data->readline_decomposer[i][j] == '\"')
			{
				i++;
				while (data->readline_decomposer[i])
				{
					data->readline_decomposer[to_switch] = data->readline_decomposer[i];
					i++;
					to_switch++;
				}
				while (data->readline_decomposer[to_switch])
				{
					data->readline_decomposer[to_switch] = "\0";
					to_switch++;
				}
				return ;
			}
			j++;
		}
		free(data->readline_decomposer[i]);
		j = 0;
		i++;
	}
}

// void	malloc_clean_decomposer(t_vault *data)
// {
// 	int	i;
// 	int	len_array;

// 	i = 0;
// 	len_array = 0;
// 	while (data->read_line[i])
// 	{
// 		if (data->read_line[i] == '\"')
// 		{
// 			i++;
// 			while (data->read_line[i] != '\"')
// 				i++;
// 			len_array++;
// 		}
// 		else if (data->read_line[i] == ' ')
// 			len_array++;
// 		i++;
// 	}
// 	data->clean_decomposer = ft_calloc(sizeof(char *), len_array + 1);
// 	if (!data->clean_decomposer)
// 	{
// 		free (data->clean_decomposer);
// 		//ajouter des free
// 		exit (EXIT_FAILURE);
// 	}
// }

// void	reduce_space(t_vault *data)
// {
// 	int		i;
// 	int		j;
// 	int		k;
// 	char	*temp;

// 	i = 0;
// 	j = 0;
// 	k = 0;
// 	while (data->readline_decomposer[i])
// 	{
// 		temp = data->readline_decomposer[i];
// 		printf("%s\n", temp);
// 		while (data->readline_decomposer[i][j])
// 		{
// 			if (data->readline_decomposer[i][j] == ' ')
// 				while (data->readline_decomposer[i][j + 1] == ' ')
// 					j++;
// 			temp[k] = data->readline_decomposer[i][j];
// 			k++;
// 			j++;
// 		}
// 		printf("%s\n", temp);
// 		k = 0;
// 		j = 0;
// 		i++;
// 	}
// }
