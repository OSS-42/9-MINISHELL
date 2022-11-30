/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:52:13 by momo              #+#    #+#             */
/*   Updated: 2022/11/30 18:36:13 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_cd(t_vault *data)
{
	if (chdir(data->rl_decomp[1]) != 0)
		perror("cd");
}

void	ft_pwd(t_vault *data)
{
	char	*pwd;
	int		size_buffer;

	(void)data;
	size_buffer = 1;
	if (data->rl_decomp[1] != NULL)
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

void	ft_echo(t_vault *data)
{
	int		i;
	int		len;
	int		j;
	int		k;
	int		len2;

	i = 1;
	len = 0;
	data->b_in->first_word = 1;
	if (!(data->rl_decomp[i]))
		return ;
	else if (ft_strcmp(data->rl_decomp[i], "-n") == 0)
	{
		i++;
		data->b_in->echo_flag_n = 1;
	}
// Gestion du $ pour variables d'environnement
// Attention :
// echo "$HOME" doit afficher la valeur de la variable,
// echo '$HOME' doit effectuer un echo normal.
// echo bonjour au revoir$HOME ==> bonjour au revoir/home/ewurstei
// echo bonjour au 'revoir$HOME' ==> bonjour au revoir$HOME
// echo bonjour au "revoir$HOME" ==> bonjour au revoir/home/ewurstei

	j = 0;
	while (data->rl_decomp[i])
	{
		while (data->rl_decomp[i][j])
		{
			if (data->rl_decomp[i][j] == '\"')
			{
				data->b_in->echo_dble_q++;
				if (data->b_in->echo_first == 0)
					data->b_in->echo_first = 2;
				if (data->b_in->echo_dble_q % 2 == 0 && data->b_in->echo_first == 2)
					data->b_in->echo_priority = 34;
			}
			else if (data->rl_decomp[i][j] == '\'')
			{
				data->b_in->echo_sgle_q++;
				if (data->b_in->echo_first == 0)
					data->b_in->echo_first = 1;
				if (data->b_in->echo_sgle_q % 2 == 0 && data->b_in->echo_first == 1)
					data->b_in->echo_priority = 39;
			}
			else if (data->rl_decomp[i][j] == '$')
				data->dollar = 1;
			j++;			
		}
		if (data->b_in->echo_priority != 0)
		{
			j = 0;
			k = 0;
			len = ft_strlen(data->rl_decomp[i]);
			data->b_in->echo_clean = ft_calloc(len + 1, sizeof(char));
			while (j < len)
			{
				if (data->rl_decomp[i][j] == data->b_in->echo_priority)
					j++;
				data->b_in->echo_clean[k] = data->rl_decomp[i][j];
				j++;
				k++;
			}
			free (data->rl_decomp[i]);
			data->rl_decomp[i] = ft_strdup(data->b_in->echo_clean);
			free (data->b_in->echo_clean);
		}
		if (data->dollar == 1)
		{
			printf("%d\n", data->b_in->echo_priority);
			if (data->b_in->echo_priority != 1)
			{
				data->activate_var = 1;
				j = 0;
				while (data->rl_decomp[i][j])
				{
					if (data->rl_decomp[i][j] == '$')
					{
						len2 = 0;
						k = j;
						while (data->rl_decomp[i][k] != ' ' && data->rl_decomp[i][k] != '\0')
						{
							len2++;
							k++;
						}
					}
					data->dollar_var = ft_substr(data->rl_decomp[i], j + 1, len2 - 1);
					data->dollar_var = ft_strjoin(data->dollar_var, "=");
					j = 0;
					while (data->env[j])
					{
						if (ft_strnstr(data->env[j], data->dollar_var, ft_strlen(data->dollar_var)) == NULL)
							j++;							
						else
							put_var_in_plain(data, j, i, len2);
					}
				}
			}
		}
		data->b_in->echo_first = 0;
		data->b_in->echo_priority = 0;
		data->dollar = 0;
		if (data->rl_decomp[i + 1] && data->rl_decomp[i + 1][0] != '\0')
		{
			print_row(data, i);
			i++;
		}
		else
		{
			print_row(data, i);
			break ;
		}
	}
	if (data->b_in->echo_flag_n == 0)
		ft_putstr_fd("\n", 1);
	return ;
}

void	put_var_in_plain(t_vault *data, int row_var, int row, int len2)
{
	int		len3;
	int		j;
	int		i;
	int		k;
	char *temp;

	j = 0;
	i = 0;
	len3 = ft_strlen(data->env[row_var]) - len2;
	temp = ft_calloc(sizeof(char), (ft_strlen(data->rl_decomp[row]) + len3 + 1));
	free (data->dollar_var);
	data->dollar_var = ft_substr(data->env[row_var], len2, len3);
	while (data->rl_decomp[row][j])
	{
		if (data->rl_decomp[row][j] == '$')
		{
			k = 0;
			while (data->dollar_var[k])
			{
				temp[i] = data->dollar_var[k];
				k++;
			}
		}
		else
			temp[i] = data->rl_decomp[row][j];
		i++;
		j++;
	}
	free (data->rl_decomp[row]);
	data->rl_decomp[row] = ft_calloc(sizeof(char), ft_strlen(temp));
	data->rl_decomp[row] = ft_strdup(temp);
	free (temp);
	return ;
}

void	print_row(t_vault *data, int row)
{	
	if (data->b_in->first_word == 1)
	{
		ft_putstr_fd(data->rl_decomp[row], 1);
		data->b_in->first_word  = 0;
	}
	else
	{
		ft_putstr_fd(" ", 1);
		ft_putstr_fd(data->rl_decomp[row], 1);
	}
	return ;
}

void	ft_exit(t_vault *data)
{
	//prevoir les free en fonction d'ou on est dans le programme lors de exit
	(void) data;
	// if (data->b_in->env_unset)
	// 	free_dbl_ptr((void **)data->b_in->env_unset);
	// if (data->b_in->env_export)
	// 	free_dbl_ptr((void **)data->b_in->env_export);
	// if (data->b_in->env_order)
	// 	free_dbl_ptr((void **)data->b_in->env_order);
//	free_dbl_ptr((void **)data->rl_decomp);
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
		while (data->b_in->env_order[i])
		{
			ft_putstr_fd(data->b_in->env_order[i], 1);
			ft_putstr_fd("\n", 1);
			i++;
		}
	}
	return ;
}
