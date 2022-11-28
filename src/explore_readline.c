/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   explore_readline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:55:29 by momo              #+#    #+#             */
/*   Updated: 2022/11/28 11:34:02 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	explore_readline(t_vault *data)
{
	data->rl_decomp = ft_split(data->read_line, ' ');
	double_quote_analyzis(data);
	if (data->double_quote_count % 2 == 0)
	{
		data->rl_decomp_i = 0;
		find_str_doublequote(data);
//		print_double_array(data->rl_decomp);
//		reduce_space(data);
		built_in(data);
	}
	return ;
}

void	built_in(t_vault *data)
{
	if (ft_strcmp("cd", data->rl_decomp[0]) == 0)
		ft_cd(data);
	if (ft_strcmp("pwd", data->rl_decomp[0]) == 0)
		ft_pwd(data);
	if (ft_strcmp("echo", data->rl_decomp[0]) == 0)
		ft_echo(data);
	if (ft_strcmp("env", data->rl_decomp[0]) == 0)
		ft_env (data, 1);
	if (ft_strcmp("export", data->rl_decomp[0]) == 0)
		ft_export (data);
	if (ft_strcmp("unset", data->rl_decomp[0]) == 0)
		ft_unset (data);
	if (ft_strcmp("exit", data->rl_decomp[0]) == 0)
		ft_exit (0);
	return ;
}

int	double_quote_analyzis(t_vault *data)
{
	int	i;

	i = 0;
	data->double_quote_count = 0;
	while (data->read_line[i])
	{
		if (data->read_line[i] == '\"')
			data->double_quote_count++;
		i++;
	}
	if (data->double_quote_count % 2 != 0)
		printf("Wrong argument\n");
	return (data->double_quote_count);
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
			while ((data->read_line[i] != '\"' || data->read_line[i + 1] > 32) && data->read_line[i])
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

	if (data->rl_decomp_i != 0)
		i = data->rl_decomp_i;
	else
		i = 0;
	while (data->rl_decomp[i])
	{
		j = 0;
		while (data->rl_decomp[i][j])
		{
			if (data->rl_decomp[i][j] == '\"')
			{
				free(data->rl_decomp[i]);
				data->rl_decomp[i] = ft_calloc(sizeof(char), len + 1);
				j = 0;
				while (begin <= end)
				{
					data->rl_decomp[i][j] = data->read_line[begin];
					begin++;
					j++;
				}
				i++;
				data->rl_decomp_i = i;
				find_decomposer_to_switch(data, i);
				return ;
			}
			j++;
		}
		i++;
	}
}

void	find_decomposer_to_switch(t_vault *data, int to_switch)
{
	int	next_array;
	int	actual_array;
	int	j;

	next_array = to_switch;
	actual_array = to_switch;
	j = 0;
	while (data->rl_decomp[next_array])
	{
		while (data->rl_decomp[next_array][j])
		{
			if (data->rl_decomp[next_array][j] == '\"')
			{
				next_array++;
				while (data->rl_decomp[next_array])
				{
					data->rl_decomp[actual_array] = data->rl_decomp[next_array];
					next_array++;
					actual_array++;
				}
				while (data->rl_decomp[actual_array])
				{
					data->rl_decomp[actual_array] = "\0";
					actual_array++;
				}
				return ;
			}
			j++;
		}
		free(data->rl_decomp[next_array]);
		j = 0;
		next_array++;
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
// 	while (data->rl_decomp[i])
// 	{
// 		temp = data->rl_decomp[i];
// 		printf("%s\n", temp);
// 		while (data->rl_decomp[i][j])
// 		{
// 			if (data->rl_decomp[i][j] == ' ')
// 				while (data->rl_decomp[i][j + 1] == ' ')
// 					j++;
// 			temp[k] = data->rl_decomp[i][j];
// 			k++;
// 			j++;
// 		}
// 		printf("%s\n", temp);
// 		k = 0;
// 		j = 0;
// 		i++;
// 	}
// }
