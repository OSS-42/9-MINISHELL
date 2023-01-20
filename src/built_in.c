/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:52:13 by momo              #+#    #+#             */
/*   Updated: 2023/01/19 20:04:07 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_cd(t_vault *data) // correction de "cd" sans argument
{
	char	*temp;
	char	*temp2;

	temp = NULL;
	temp2 = NULL;
	if (data->flag->pipe_count != 0)
		return ;
	if (data->cmd->opt[1] == NULL)
	{
		temp = ft_strdup(data->cmd->opt[0]);
		ft_dbl_ptr_free ((void **)data->cmd->opt);
		data->cmd->opt = ft_calloc(sizeof(char *), 3);
		data->cmd->opt[0] = ft_strdup(temp);
		free (temp);
		temp2 = check_env_home_exist(data);
		if (temp2 == NULL)
		{
			error_message(data, "HOME not set", "1\0");
			put_code_in_fd("1\0", data->error_fd);
			free (temp2);
			return ;
		}
		else
		{
			data->cmd->opt[1] = ft_strdup(temp2);
			free(temp2);
		}
	}
	if (chdir(data->cmd->opt[1]) != 0)
	{
		error_message(data, "no such file or directory", "1\0");
		put_code_in_fd("1\0", data->error_fd);
	}
	put_code_in_fd("0\0", data->error_fd);
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
	put_code_in_fd("0\0", data->error_fd);
	free (pwd);
}

void	ft_exit(t_vault *data)
{
	if (data->flag->rl_exit == 0 && data->flag->exit_fork != 1)
		close_pipe(data);
	if (getenv("PATH") && data->env && data->cmd->opt)
	{
		if ((data->cmd->opt[1] && data->cmd->opt[2])
			|| (data->cmd->opt[1] && ft_is_str_digit(data->cmd->opt[1]) == 0))
			put_code_in_fd("2\0", data->error_fd);
		else if (data->cmd->opt && data->cmd->opt[1]
			&& ft_atoi(data->cmd->opt[1]) < 257)
			good_code_format(data);
	}
	data->temp_str = find_error_code(data);
	g_error_code = ft_atoi(data->temp_str);
	ft_free_n_null (data->temp_str);
	data->temp_str = NULL;
	if (data->flag->exit_fork != 1)
	{
		exit_minishell();
		clear_history ();
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
	put_code_in_fd("0\0", data->error_fd);
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
	put_code_in_fd("0\0", data->error_fd);
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
