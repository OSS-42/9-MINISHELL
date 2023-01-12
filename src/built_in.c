/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbertin <mbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:52:13 by momo              #+#    #+#             */
/*   Updated: 2023/01/12 09:22:34 by mbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_cd(t_vault *data)
{
	if (data->flag->pipe_count != 0)
		return ;
	if (chdir(data->cmd->opt[1]) != 0)
		error_message(data, "no such file or directory", "1\0");
	else
		on_success(data);
}

void	ft_pwd(t_vault *data)
{
	char	*pwd;
	int		size_buffer;

	(void) data;
	size_buffer = 1;
	pwd = calloc(sizeof(char), size_buffer);
	while (getcwd(pwd, size_buffer) == NULL)
	{
		free (pwd);
		size_buffer++;
		pwd = calloc(sizeof(char), size_buffer);
	}
	ft_putstr_fd(pwd, 1);
	write(1, "\n", 1);
	on_success(data);
	free (pwd);
}

void	ft_exit(t_vault *data)
{
	if (data->flag->rl_exit == 0 && data->flag->exit_fork != 1)
		close_pipe(data);
	if (data->cmd->opt && data->cmd->opt[1] && ft_atoi(data->cmd->opt[1]) < 256)
	{
		data->error_fd = open("/tmp/.tmp_error", O_CREAT
				| O_WRONLY | O_TRUNC, 0644);
		ft_putstr_fd(data->cmd->opt[1], data->error_fd);
		close(data->error_fd);
	}
	data->temp_str = find_error_code(data);
	g_error_code = ft_atoi(data->temp_str);
	ft_free_n_null (data->temp_str);
	data->temp_str = NULL;
	if (data->flag->exit_fork != 1)
	{
		exit_minishell();
		unlink("/tmp/.tmp_error");
	}
	clean_before_exit(data);
	exit(g_error_code);
}

void	ft_env(t_vault *data, int env)
{
	int	i;

	i = -1;
	if (env == 1)
	{
		while (data->env[++i])
		{
			ft_putstr_fd(data->env[i], 1);
			ft_putstr_fd("\n", 1);
		}
	}
	else if (env == 2)
	{
		while (data->b_in->env_ord[++i])
		{
			ft_putstr_fd(data->b_in->env_ord[i], 1);
			ft_putstr_fd("\n", 1);
			ft_free_n_null (data->b_in->env_ord[i]);
			data->b_in->env_ord[i] = NULL;
		}
		free (data->b_in->env_ord);
		data->b_in->env_ord = NULL;
	}
	on_success(data);
	return ;
}

void	ft_echo(t_vault *data, int line)
{
	int	i;

	i = 1;
	data->b_in->forget_minus = 0;
	data->b_in->minus_n = 0;
	data->b_in->dont_do_minus = 0;
	parse_minus(data);
	if (data->b_in->minus_n == 1)
		recompose_tab_arg(data, line);
	data->b_in->first_word = 1;
	data->b_in->echo_flag_n = 0;
	while (data->cmd->opt[i])
	{
		print_row(data, i);
		i++;
	}
	if (data->b_in->minus_n == 0)
		ft_putstr_fd("\n", STDOUT_FILENO);
	data->b_in->forget_minus = 0;
	on_success(data);
	return ;
}

// tests au 11/01 a 13:40
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
//echo $ USER						|		OK
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
