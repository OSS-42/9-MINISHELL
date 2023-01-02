/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbertin <mbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:52:13 by momo              #+#    #+#             */
/*   Updated: 2023/01/02 08:28:01 by mbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_cd(t_vault *data)
{
	if (data->flag->pipe_count != 0)
		return ;
	if (chdir(data->cmd->opt[1]) != 0)
	{
		ft_putstr_fd("1\0", data->error_fd);
		error_message(data, "no such file or directory");
	}
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
	free (pwd);
}

void	ft_exit(t_vault *data)
{
	if (data->b_in->export_var)
		free (data->b_in->export_var);
	if (data->b_in->env_export)
		ft_dbl_ptr_free((void **)data->b_in->env_export);
	if (data->b_in->env_unset)
		ft_dbl_ptr_free((void **)data->b_in->env_unset);
	if (data->b_in->env_ord)
		free(data->b_in->env_ord);
	if (data->read_line)
		free(data->read_line);
	if (data->b_in)
		free(data->b_in);
	if (data->quote)
		free(data->quote);
	if (data->flag)
		free(data->flag);
	if (data->tab_arg)
		ft_dbl_ptr_free((void **)data->tab_arg);
	free (data->cmd->name);
//	free(data->pid);
	unlink(".temp_error");
	exit (g_error_code);
}
	//ne pas oublier exit_minishell();

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
	data->b_in->forget_minus = 0;
	data->b_in->minus_n = 0;
	data->b_in->dont_do_minus = 0;
	parse_minus(data);
	if (data->b_in->minus_n == 1)
		recompose_tab_arg(data, line);
	data->b_in->first_word = 1;
	data->b_in->echo_flag_n = 0;
	print_row(data, line);
	if (data->b_in->minus_n == 0)
		ft_putstr_fd("\n", 1);
	data->b_in->forget_minus = 0;
	return ;
}

// tests au 31/12 a 14h
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
//echo $"USER"						|			KO segfault
//echo $USERA						|		OK
//echo $USER$TERM					|		OK
//echo "$USER"						|		OK
//echo '$USER'						|		OK
//echo "'$USER'"					|		OK
//echo '"$USER"'					|		OK
//echo '$USER'$TERM					|			KO espace en trop
//echo "$USER"'$TERM'				|			KO espace en trop
//echo $USER'$TERM					|			KO espace en trop
//echo $USER"$TERM"					|			KO espace en trop
//echo $USER $TERM					|		OK
//echo $USER $TERM $HOME			|		OK
//echo $USER $TErM					|		OK
//echo $USER $TErM $HOME			|		OK
//echo "bonjour $USER"				|		OK
//echo "bonjour '$USER'"			|		OK
//echo "a"b'c'						|			KO espace en trop
//echo ""x''y						|			KO espace en trop
//echo 1' '2" "3					|			KO espaces en trop
//echo "$USER "$USER" $TERM '$PATH'"|		OK