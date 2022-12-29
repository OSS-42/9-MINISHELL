/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:52:13 by momo              #+#    #+#             */
/*   Updated: 2022/12/29 17:41:41 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_cd(t_vault *data)
{
	if (data->flag->pipe_count != 0)
		return ;
	if (chdir(data->cmd->opt[1]) != 0)
	{
		g_error_code = 4;
		perror("cd");
		// ft_exit(data);
	}
}

void	ft_pwd(t_vault *data)
{
	char	*pwd;
	int		size_buffer;

	size_buffer = 1;
	if (data->cmd->opt[1] != NULL)
	{
		g_error_code = 10;
		write(2, "pwd: too many arguments\n", 24);
		// ft_exit(data);
	}
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
	if (g_error_code == 1)
		message(data, "path or env missing", 1);
	if (g_error_code == 2)
		message(data, "EOF on readline", 1);
	if (g_error_code == 3)
		message(data, "FD error", 1);
	if (g_error_code == 4)
		message(data, "no such file or directory", 1);
	if (g_error_code == 5)
		message(data, "I/O error (dup2)", 1);
	if (g_error_code == 6)
		message(data, "heredoc: no such file or directory", 1);
	if (g_error_code == 7)
		message(data, "heredoc: I/O error ", 1);
	if (g_error_code == 8)
		message(data, "pipe creation error", 1);
	if (g_error_code == 9)
		message(data, "pid creation error", 1);
	if (g_error_code == 10)
		message(data, "missing or wrong arguments", 1);
	if (g_error_code == 11)
		message(data, "command not found", 1);
	free_all(data);
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

void	ft_echo(t_vault *data, int line)
{
	parse_minus(data);
	if (data->b_in->minus_n == 1)
		recompose_tab_arg(data, line);
	data->b_in->first_word = 1;
	data->b_in->echo_flag_n = 0;
	print_row(data, line);
	if (data->b_in->minus_n == 0)
		ft_putstr_fd("\n", 1);
	return ;
}



//echo $$ ou echo $!, etc pas gerer (on affiche juste les caracteres).
//echo '-n' ou echo "-n" doivent renvoyer vers echo_minus.
//			TESTS					|	RESULTS
//-------------------------------------------------
//echo								|		OK
//echo bonjour						|		OK
//echo -n							|		OK
//echo salut bonjour				|		OK
//echo -n salut						|		OK
//echo -n salut bonjour				|		OK
//echo salut -n						|		OK
//echo salut bonjour -n				|		OK
//echo -n bonjour -n				|		OK
//echo "-n salut bonjour"			|		OK
//echo '-n salut bonjour'			|		OK
//echo "-n" salut bonjour			|		OK
//echo '-n' salut bonjour			|		OK
//echo -n -n salut bonjour			|		OK
//echo -n4 -n salut bonjour			|		OK
//echo -n -n4 salut bonjour			|		OK
//echo "-n -n" salut bonjour		|		OK
//echo -nnn -nnn salut bonjour		|		OK
//echo --n salut bonjour			|		OK
//echo "--n" salut bonjour			|		OK
//echo '--n' salut bonjour			|		OK
//echo "--n salut bonjour"			|		OK
//echo $USER						|		OK
//echo $"USER"						|		OK
//echo $USERA						|		OK
//echo $USER$TERM					|		OK
//echo "$USER"						|		OK
//echo '$USER'						|		OK
//echo "'$USER'"					|		OK
//echo '"$USER"'					|		OK
//echo '$USER'$TERM					|		OK
//echo "$USER"'$TERM'				|		OK
//echo $USER'$TERM					|		OK
//echo $USER"$TERM"					|		OK
//echo $USER $TERM					|		OK
//echo $USER $TERM $HOME			|		OK
//echo $USER $TErM					|		OK
//echo $USER $TErM $HOME			|		OK
//echo "bonjour $USER"				|		OK
//echo "bonjour '$USER'"			|		OK
//echo "a"b'c'						|		OK
//echo ""x''y						|		OK
//echo 1' '2" "3					|		OK
//echo "$USER "$USER" $TERM '$PATH'"|		OK