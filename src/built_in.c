/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:52:13 by momo              #+#    #+#             */
/*   Updated: 2022/12/19 14:02:06 by ewurstei         ###   ########.fr       */
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
	// if (data->rl_decomp)
	// 	free_dbl_ptr((void **)data->rl_decomp);
	if (data->b_in->export_var)
		free (data->b_in->export_var);
	if (data->b_in->env_export)
		free_dbl_ptr((void **)data->b_in->env_export);
	if (data->b_in->env_unset)
		free_dbl_ptr((void **)data->b_in->env_unset);
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
	int	line;
	int	tab_len;

	line = 1;
	tab_len = ft_dbl_ptr_len(data->rl_decomp);
	data->b_in->first_word = 1;
	data->b_in->echo_flag_n = 0;
	while (line < tab_len)
	{
		if (data->rl_decomp[row] && data->rl_decomp[row][0])
		{
				print_row(data, row);
				data->b_in->echo_flag_n = 0;
		}
		row++;
		line++;
	}
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
//echo -n							|			KO (ne pas afficher le -n)
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