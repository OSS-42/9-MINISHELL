/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbertin <mbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:52:13 by momo              #+#    #+#             */
/*   Updated: 2022/11/22 15:03:59 by mbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_cd(t_vault *data)
{
	if (chdir(data->readline_decomposer[1]) != 0)
		perror("cd");
}

void	ft_pwd(t_vault *data)
{
	char	*pwd;
	int		size_buffer;

	(void)data;
	size_buffer = 1;
	if (data->readline_decomposer[1] != NULL)
		write(2, "pwd: too many arguments\n", 24);
	else
	{
		pwd = calloc(sizeof(char), size_buffer);
		while (getcwd(pwd, size_buffer) == NULL)
		{
			free (pwd);
			size_buffer++;
			pwd = calloc(sizeof(char), size_buffer);
		}
		// if (pwd == NULL)
		// 	perror("");
		ft_putstr_fd(pwd, 1);
		write(1, "\n", 1);
	}
}

void	ft_echo(t_vault *data)
{
	char	**echo_args;
	int		i;
	int		flag_n;

	i = 1;
	flag_n = 0;
	if (echo_args[1] == "-n")
	{
		i = 2;
		flag_n = 1;
	}
	echo_args = ft_split(data, " ");
	while (echo_args[i])
	{
		ft_putstr_fd(echo_args[i], 1);
		i++;
	}
	if (flag_n == 0)
		ft_putstr_fd("\n", 1);
	else
		return ;
}
