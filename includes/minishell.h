/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbertin <mbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 19:18:06 by ewurstei          #+#    #+#             */
/*   Updated: 2022/11/22 08:47:38 by mbertin          ###   ########.fr       */
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

/***** STRUTUCE *****/

typedef struct s_data
{
	int		argc;
	char	**argv;
	char	**env;
	char	*read_line;
	char	**split_readline;
}	t_data;

/***** minishell.c *****/

void	malloc_struct(t_data **data, int argc, char **argv, char **env);
void	init_struct(t_data *data, int argc, char **argv, char **env);
void	explore_readline(t_data	*data);

/**** BUILT_IN ****/

void	ft_cd(t_data *data);

/***** POUR DEBUG *****/

void	print_double_array(char **array);

#endif