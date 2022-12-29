/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbertin <mbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 19:18:06 by ewurstei          #+#    #+#             */
/*   Updated: 2022/12/29 14:25:15 by mbertin          ###   ########.fr       */
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
# include <signal.h>
# include "../libft/includes/libft.h"
# include "../librl/readline.h"
# include "../librl/history.h"
# include "../libart/includes/libart.h"

/***** DEFINES *****/
# define TRUE 1
# define FALSE 0
# define ALIVE 1
# define EXEC 2

enum	e_pipe_ends_name
{
	p_read,
	p_write
};

/***** STRUTURES *****/
typedef struct s_cmd
{
	char	*path;
	char	*name;
	char	**opt;
}	t_cmd;

typedef struct s_builtins
{
	char	**env_unset;
	char	**env_export;
	char	**env_ord;
	char	*unset_arg;
	char	*exp_arg;
	char	*export_var;
	// char	*order_var; //pas trouve, a supprimer ?
	// char	*echo_var; //pas trouve, a supprimer ?
	// char	echo_priority; //pas trouve, a supprimer ?
	// int		echo_first; //pas utilise, a supprimer ?
	int		echo_flag_n;
	int		minus_n;
	// int		echo_dble_q; //pas trouve, a supprimer ?
	// int		echo_sgle_q; //pas trouve, a supprimer ?
	int		forget_minus;
	int		dont_do_minus;
	int		first_word;
}	t_builtins;

typedef struct s_flag
{
	char	*output;
	// int		*fd_out; //pas trouve, a supprimer ?
	// int		output_count; //trouve seulement incrementation, aucune utilisation, a supprimer ?
	// int		chevron_count; //pas trouve, a supprimer ?
	// int		input_count; //trouve seulement incrementation, aucune utilisation, a supprimer ?
	int		pipe_count;
	int		stdout_backup;
	int		stdin_backup;
	int		var_not_found;
	char	chevron;
	int		append;
	int		heredoc_delimiter;
	int		heredoc_fd;
	int		fd;
	int		**pipe;
}	t_flag;

typedef struct s_quote
{
	int		double_quote_count;
	int		simple_quote_count;
	int		len_of_replacement;
	int		last_replace;
	int		begin;
	char	quote_priority;
	char	temp_priority;
	char	**buffer;
}	t_quote;

typedef struct s_vault
{
	char		**env;
	char		**rl_dec;
	// char		**clean_decomposer; //pas trouve, a supprimer ?
	char		**tab_arg;
	char		**path_names;
	char		**temp;
	char		*read_line;
	// char		*env_path; //pas trouve, a supprimer ?
	// char		*test; //pas trouve, a supprimer ?
	char		*buffer;
	t_builtins	*b_in;
	t_quote		*quote;
	t_flag		*flag;
	t_cmd		*cmd;
	char		*dollar_var;
	char		*paths;
	int			dollar_var_len;
	int			spc_count;
	int			pos;
	int			begin;
	// int			fd_in; //trouve juste initialisation a -1, aucune utilisation, a supprimer ?
	// int			fd_out; //trouve juste initialisation a -1, aucune utilisation, a supprimer ?
	// int			fork_count; //trouve juste initialisation a 0, aucune utilisation, a supprimer ?
	pid_t		*pid;
	int			child_id;
	int			status;
	int			exit_code;
	// int			debug; //pas trouve, a supprimer ?
}	t_vault;

/***** minishell.c *****/
void	init_data(t_vault *data);
void	reinit_data(t_vault *data);
void	readline_exec(t_vault *data);
void	launch_minishell(t_vault *data);

/***** explore_readline.c *****/
void	explore_readline(t_vault *data);
void	piping(t_vault *data);
void	launching_exec(t_vault *data);
void	forking(t_vault *data, int line, int type);
void	child_creation(t_vault *data, int line);

/***** explore_utils.c *****/
void	built_in(t_vault *data, int line);
int		is_built_in(char *str);
void	recompose_tab_arg(t_vault *data, int line);

/***** meta_analyzis.c *****/
int		rl_prio_n_qty(t_vault *data, int i, char c);
void	flag_count(t_vault *data, int i, int j);

/***** redirection_management.c *****/
void	execute_redirection(t_vault *data, int i, int j);
void	redirection(t_vault *data, char *redirection);
void	stdout_redirection(t_vault *data, char *redirection);
void	stdin_redirection(t_vault *data, char *redirection);

/***** redir_in_same_array.c *****/
void	redir_in_same_array(t_vault *data, int i, int *j, char c);
void	find_redir_in_same_array(t_vault *data, char *rl_dec_array);
void	len_of_redir(t_vault *data, char *rl_dec_array);

/***** redir_in_same_array_2.c *****/
void	clean_redir(t_vault *data, int i);
char	*clean_redir_from_zero(t_vault *data, int i, char *str, int begin);
int		while_not_chevron(t_vault *data, int i, char *str, int *begin);
int		len_without_redir(t_vault *data, int i, int temp, int *begin);
int		len_from_chevron_at_zero(t_vault *data, int i, int *begin);

/***** redir_in_next_array.c *****/
void	redir_in_next_array(t_vault *data, int i, int *j, char c);
void	find_redir_in_next_array(t_vault *data, char *rl_dec_array);
void	clean_redir_next_array(t_vault *data, int i);
void	token_without_redir_name(t_vault *data, int i, int begin, int len);

/***** redirection_utils.c *****/
char	*clean_the_chevron(t_vault *data, char *str, int i, int j);
int		flag_in_str(char *str);
int		while_is_not_flag(char *str, int i);
int		while_quote(t_vault *data, char *str, int i);

/***** redirection_utils_2.c *****/
void	dup_from_begin(t_vault *data, int i, int j, char *temp);

/***** quote_management.c *****/
void	find_str_quote(t_vault *data);
void	len_of_replacement(t_vault *data, int *i);
void	begin_of_new_replacement(t_vault *data, int *rl_index);
void	len_after_quote(t_vault *data, int *rl_index);

/***** quote_management_2.c *****/
void	find_decomposer_array_to_replace(t_vault *data, int end);
void	replace_decomposer_array(t_vault *data, int end, int *i);
void	find_decomposer_to_switch(t_vault *data, int to_switch);

/***** built_in.c *****/
void	ft_cd(t_vault *data);
void	ft_pwd(t_vault *data);
void	ft_exit(t_vault *data, int error_code);
void	ft_env(t_vault *data, int env);
void	ft_echo(t_vault *data, int line);

/***** parsing_utils ******/
int		check_next_char(t_vault *data, int row, int i);
void	parse_row(t_vault *data, int row);
int		sgle_quote_mngmt(t_vault *data, int row, int i);
int		dble_quote_mngmt(t_vault *data, int row, int i);
void	row_parsing(t_vault *data);
int		check_is_redir(t_vault *data, int row, int i);

/***** built_in2.c *****/
void	ft_unset(t_vault *data, int line);
void	remove_line_env(t_vault *data, int i);
void	ft_export(t_vault *data, int line);
void	add_line_env(t_vault *data);
void	order_env(t_vault *data);

/***** personnal_fonction.c *****/
int		check_if_inside_quote(char *str, char c);
void	print_double_array(char **array);
//int		dbl_array_len(char **array);

/***** error_mgmnt.c *****/
int		check_error(t_vault *data, int row);
void	exit_on_error(t_vault *data, int error_code);
int		message(t_vault *data, char *str1, char *str2, int error_code);

/***** minishell_utils.c *****/
void	print_row(t_vault *data, int line);
int		ft_isinset(char c);
void	export_only_format(t_vault *data, char *buff2, char **temp, int i);

/***** built_in_utils.c *****/
void	join_unset(t_vault *data, int line);
void	swap_lines(t_vault *data, int rows);
void	dup_env(t_vault *data);
void	var_prep(t_vault *data, int line);
void	copy_env(t_vault *data, char **temp, int i);

/***** dollar_utils.c *****/
int		dollar_var_to_extract(t_vault *data, int row, int i);
char	*var_extract(t_vault *data, int row, int position);
char	*does_var_exist(t_vault *data);
char	*expand_var(t_vault *data, int row_var);

/***** minus_utils. *****/
void	parse_minus(t_vault *data);
void	recreate_arg_tab(t_vault *data, char **tab);
char	**create_temp_swap(t_vault *data, int row);
void	check_minus_validity(t_vault *data, int row, int i);

/***** pipe_utils.c *****/
void	create_tab_arg(t_vault *data, int row, int line);
void	switch_lines(t_vault *data, int row, int line);
void	do_the_switch(t_vault *data, int line);

/***** heredoc.c *****/
void	heredoc(t_vault *data);

/***** prog_utils.c *****/
void	find_paths(t_vault *data);
void	cmd_path_check(t_vault *data);
void	find_prog(t_vault *data, int line);

/***** io_utils.c *****/
void	io_redirection(t_vault *data, int input, int output);
int		dup_fds(t_vault *data, int line);
void	close_pipe(t_vault *data);
void	reset_io(t_vault *data);

/***** detached_quote.c *****/
void	detached_quote_tab(t_vault *data);
int		len_detached_quote_tab(t_vault *data);
void	quote_to_quote(t_vault *data, int row, int *line, int *len);
void	fill_detached_quote_tab(t_vault *data);
void	row_with_quote(t_vault *data, int *i, int row, int *line);

/***** detached_quote_utils.c *****/
int		len_in_quote_dtch(t_vault *data, int line, int row);
int		len_out_quote_dtch(t_vault *data, int row, int line);
void	fill_out_quote(t_vault *data, int *i, int row, int *line);
void	fill_in_quote(t_vault *data, int *i, int row, int *line);

/***** pipe_management.c *****/
void	check_for_pipe(t_vault *data);
void	expand_tab(t_vault *data, int len);
void	search_for_pipe(t_vault *data, int row, int *i);

/***** signal_management.c *****/
void	init_signal(int mode);
void	interrupt_alive(int sig);
void	quit_alive(int sig);
void	interrupt_exec(int sig);
void	quit_exec(int sig);
//t_vault	*get_data(void);

#endif