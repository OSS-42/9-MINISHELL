/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbertin <mbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 19:18:06 by ewurstei          #+#    #+#             */
/*   Updated: 2022/11/24 14:19:21 by mbertin          ###   ########.fr       */
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

/***** STRUTURE *****/

typedef struct s_vault
{
	char	*env_path;
	char	*read_line;
	char	**readline_decomposer;
	char	**clean_decomposer;
}	t_vault;

/***** minishell.c *****/

void	init_struct(t_vault **data);

/***** explore_readline.c *****/

void	explore_readline(t_vault	*data);
void	find_str_doublequote(t_vault *data);
void	replace_decomposer_array(t_vault *data, int len, int begin, int end);
void	find_decomposer_to_switch(t_vault *data, int i);
void	malloc_clean_decomposer(t_vault *data);
// void	reduce_space(t_vault *data);
void	built_in(t_vault *data);

/**** built_in.c ****/

void	ft_cd(t_vault *data);
void	ft_pwd(t_vault *data);
void	ft_echo(t_vault *data);
void	ft_exit(t_vault *data);

/***** POUR DEBUG *****/

void	print_double_array(char **array);

#endif