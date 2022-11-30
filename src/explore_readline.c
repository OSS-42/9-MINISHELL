/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   explore_readline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:55:29 by momo              #+#    #+#             */
/*   Updated: 2022/11/29 23:01:16 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	explore_readline(t_vault *data)
{
	data->rl_decomp = ft_split(data->read_line, ' ');
	meta_analyzis(data);
	// print_double_array(data->rl_decomp);
	// write(1, "\n", 1);
	if (data->quote_in->double_quote_count % 2 == 0)
	{
		data->rl_decomp_i = 0;
		find_str_quote(data);
//		print_double_array(data->rl_decomp);
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
