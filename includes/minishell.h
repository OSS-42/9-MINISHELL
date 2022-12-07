/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 19:18:06 by ewurstei          #+#    #+#             */
/*   Updated: 2022/12/07 00:53:03 by ewurstei         ###   ########.fr       */
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
	char	**env_ord;
	char	*unset_arg;
	char	*exp_arg;
	char	*export_var;
	char	*order_var;
	char	*echo_var;
	int		echo_flag_n;
	char	echo_priority;
	int		echo_first;
	int		echo_dble_q;
	int		echo_sgle_q;
	int		flag_clean_echo;
	int		first_word;
}	t_builtins;

typedef struct s_flag
{
	char	**output;
	int		output_count;
	int		input_count;
	int		pipe_count;
	int		dollar_count;
	int		dollar_split;
	int		*fd_out;
	int		runs;
	int		stdout_backup;

}	t_flag;

typedef struct s_quote
{
	int		double_quote_count;
	int		simple_quote_count;
	int		len;
	int		begin;
	char	quote;
	int		spc_count;
}	t_quote;

typedef struct s_vault
{
	char		*read_line;
	char		*env_path;
	char		**env;
	char		**clean_decomposer;
	int			rl_decomp_i;
	char		**rl_decomp;
	char		*test;
	t_builtins	*b_in;
	t_quote		*quote_in;
	t_flag		*flag;
	int			activate_var;
	char		*dollar_var;
	int			dollar_var_len;
	char		**split_dollar;
}	t_vault;

/***** minishell.c *****/
void	init_data(t_vault *data);
void	reinit_data(t_vault *data);

/***** explore_readline.c *****/
void	explore_readline(t_vault *data);
void	built_in(t_vault *data);
void	execute_redirection(t_vault *data);
// void	reduce_space(t_vault *data);
// void	malloc_clean_decomposer(t_vault *data);

/***** meta_analyzis.c *****/
int		readline_quote_priority(t_vault *data);
char	*output_to_redirect(t_vault *data, int i, int j);
void	redirection_analysiz(t_vault *data);
void	flag_count(t_vault *data);

/***** double_quote_management.c *****/
void	find_str_quote(t_vault *data);
void	decomposer_array_to_replace(t_vault *data, int end);
void	replace_decomposer_array(t_vault *data, int end, int *i);
void	find_decomposer_to_switch(t_vault *data, int to_switch);
void	switch_decomposer(t_vault *data, int *next_array, int *actual_array);
void	len_of_replacement(t_vault *data, int *i);

/***** built_in.c *****/
void	ft_cd(t_vault *data, int row);
void	ft_pwd(t_vault *data, int row);
void	ft_echo(t_vault *data, int row);
void	ft_exit(t_vault *data);
void	ft_env(t_vault *data, int env);

/***** ft_echo_utils ******/
int		quote_priority(t_vault *data, int row);
void	clean_quote(t_vault *data, int row);
void	find_var_value(t_vault *data, int row);
void	var_extract(t_vault *data, int row, int position);
void	expand_var(t_vault *data, int row_var, int row);
//void	expand_var(t_vault *data, int row_var, int row, char **array);

/***** built_in2.c *****/
void	ft_unset(t_vault *data, int row);
void	remove_line_env(t_vault *data, int i);
void	ft_export(t_vault *data, int row);
void	add_line_env(t_vault *data);
void	order_env(t_vault *data);

/***** personnal_fonction.c *****/
int		check_if_inside_quote(char *str, char c);

/***** error_mgmnt.c *****/
int		check_error(t_vault *data, int row);

/***** minishell_utils.c *****/
void	print_row(t_vault *data, int row);
void	spe_char(t_vault *data, int row);
void	reset_counters(t_vault *data);

/***** built_in_utils.c *****/
void	join_unset(t_vault *data, int row);
void	swap_lines(t_vault *data, int rows);
void	dup_env(t_vault *data);
void	var_prep(t_vault *data, int row);

//void	var_extract(t_vault *data, int row, int position, char **array);

/***** dollar_utils.c *****/
void	var_to_value(t_vault *data, int row, char *temp);
void	split_on_dollar(t_vault *data, int row);
int		insert_row(int pos, int count, char **dest, char **source);
void	change_tab(t_vault *data, char **dest, int row);
int		copy_var(char *dest, char *source, int pos);

/***** POUR DEBUG *****/
void	print_double_array(char **array);

#endif