/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:52:13 by momo              #+#    #+#             */
/*   Updated: 2022/11/23 11:02:33 by ewurstei         ###   ########.fr       */
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
		free (pwd);
	}
}

void	ft_echo(t_vault *data)
{
	int		i;
	int		flag_n;

	i = 1;
	flag_n = 0;
	if (!(data->readline_decomposer[1]))
		return ;
	else if (ft_strcmp(data->readline_decomposer[1], "-n") == 1)
	{
		i = 2;
		flag_n = 1;
	}
	while (data->readline_decomposer[i])
	{
		if (data->readline_decomposer[i])
			ft_putstr_fd(data->readline_decomposer[i], 1);
		else
			break ;
		i++;
	}
	if (flag_n == 0)
		ft_putstr_fd("\n", 1);
	else
		return ;
}
