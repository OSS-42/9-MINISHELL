/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:52:13 by momo              #+#    #+#             */
/*   Updated: 2022/12/06 21:34:32 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_cd(t_vault *data, int row)
{
	if (chdir(data->rl_decomp[row]) != 0)
		perror("cd");
}

void	ft_pwd(t_vault *data, int row)
{
	char	*pwd;
	int		size_buffer;

	(void)data;
	size_buffer = 1;
	if (data->rl_decomp[row] != NULL)
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
		ft_putstr_fd(pwd, 1);
		write(1, "\n", 1);
		free (pwd);
	}
}

void	ft_exit(t_vault *data)
{
	free_dbl_ptr((void **)data->rl_decomp);
	free (data->b_in->export_var);
	if (data->b_in->env_export)
		free_dbl_ptr((void **)data->b_in->env_export);
	if (data->b_in->env_unset)
		free_dbl_ptr((void **)data->b_in->env_unset);
	if (data->b_in->env_ord)
		free(data->b_in->env_ord);
	free(data->read_line);
	free(data->b_in);
	free(data->quote_in);
	free(data->flag);
	free (data->dollar_var);
	exit (0);
}

void	ft_env(t_vault *data, int env)
{
	int	i;

	i = 0;
	if (env == 1)
	{
		while (data->env[i])
		{
			ft_putstr_fd(data->env[i], 1);
			ft_putstr_fd("\n", 1);
			i++;
		}
	}
	else if (env == 2)
	{
		while (data->b_in->env_ord[i])
		{
			ft_putstr_fd(data->b_in->env_ord[i], 1);
			ft_putstr_fd("\n", 1);
			free (data->b_in->env_ord[i]);
			i++;
		}
	}
	return ;
}

void	ft_echo(t_vault *data, int row)
{
	data->b_in->first_word = 1;
	if (!(data->rl_decomp[row]))
		return ;
	else if (ft_strcmp(data->rl_decomp[row], "-n") == 0)
	{
		row++;
		data->b_in->echo_flag_n = 1;
	}
	while (data->rl_decomp[row])
	{
		print_row(data, row);
		if (data->rl_decomp[row + 1] && data->rl_decomp[row + 1][0] != '\0')
			row++;
		else
			break ;
	}
	if (data->b_in->echo_flag_n == 0)
		ft_putstr_fd("\n", 1);
	data->b_in->echo_flag_n = 0;
	return ;
}
