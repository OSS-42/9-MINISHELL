/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 19:18:06 by ewurstei          #+#    #+#             */
/*   Updated: 2022/11/25 16:08:33 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include <curses.h>
# include "../libft/includes/libft.h"
# include "../librl/readline.h"
# include "../librl/history.h"

# define TRUE 1
# define FALSE 0

# define INTRO "\
#/bin/bash \n\
bash pretty/intro_minishell.sh \n\
"

/***** STRUTURE *****/

typedef struct s_builtins
{
	char	**env_unset;
	char	**env_export;
	char	**env_order;
	char	*unset_arg;
	char	*export_arg;
	char	*export_var;
	char	*order_var;
}	t_builtins;

typedef struct s_vault
{
	char		*env_path;
	char		**env;
	char		*read_line;
	char		**rl_decomp;
	char		*test;
	t_builtins	*b_in;
}	t_vault;

/***** minishell.c *****/

/***** explore_readline.c *****/
void	explore_readline(t_vault *data);
void	built_in(t_vault *data);

/***** built_in.c *****/
void	ft_cd(t_vault *data);
void	ft_pwd(t_vault *data);
void	ft_echo(t_vault *data);
void	ft_exit(t_vault *data);
void	ft_env(t_vault *data, int env);

/***** built_in2.c *****/
void	ft_unset(t_vault *data);
void	remove_line(t_vault *data, int i);
void	ft_export(t_vault *data);
void	add_line_env(t_vault *data, int i);
void	order_env(t_vault *data);

/***** POUR DEBUG *****/
void	print_double_array(char **array);

#endif