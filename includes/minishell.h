/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 19:18:06 by ewurstei          #+#    #+#             */
/*   Updated: 2023/01/20 12:33:09 by ewurstei         ###   ########.fr       */
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

/***** GLOBAL *****/
extern int	g_error_code;

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
	char	*name_path;
	char	**opt;
	char	**output;
}	t_cmd;

typedef struct s_builtins
{
	char	**env_unset;
	char	**env_export;
	char	**env_ord;
	char	*unset_arg;
	char	*exp_arg;
	char	*export_var;
	int		echo_flag_n;
	int		minus_n;
	int		forget_minus;
	int		dont_do_minus;
	int		first_word;
}	t_builtins;

typedef struct s_flag
{
	char	*output;
	int		pipe_count;
	int		stdout_backup;
	int		stdin_backup;
	int		var_not_found;
	char	chevron;
	int		append;
	int		heredoc_delimiter;
	int		heredoc_fd;
	int		heredoc;
	int		fd;
	int		fd_out;
	int		**pipe;
	int		execve;
	int		rl_exit;
	int		exit_fork;
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
	char		**tab_arg;
	char		**path_names;
	char		**temp;
	char		*temp_str;
	char		*read_line;
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
	pid_t		*pid;
	int			child_id;
	int			status;
	int			fail_redir;
	int			error_fd;
}	t_vault;

/***** minishell.c *****/
void	readline_exec(t_vault *data);
void	launch_minishell(t_vault *data);
void	readline_error(t_vault *data, int i);

/***** init_data.c *****/
void	init_data(t_vault *dat, char **env);
void	reinit_data(t_vault *data);
void	reinit_fd(t_vault *data);
void	cmd_prep(t_vault *data, int i);

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
int		is_special_built_in(t_vault *data, int line);
void	in_child_exec(t_vault *data, int line);

/***** meta_analyzis.c *****/
int		rl_prio_n_qty(t_vault *data, int i, char c);
void	flag_count(t_vault *data, int i, int j);
int		pipe_check(t_vault *data);
int		move_index_delimiter(t_vault *data, int i, char delimiter);
int		check_pipe_syntax(t_vault *data, int i);

/***** meta_analyzis2.c *****/
void	quote_iteration(t_vault *data, int *i);
int		pipe_after_chevron(t_vault *data, int i);
int		triple_chevron(t_vault *data, int i);
int		opposite_chevron(t_vault *data, int i);
int		chevron_space_chevron(t_vault *data, int i);

/***** redirection_management.c *****/
void	execute_redirection(t_vault *data, int i, int j);
void	redirection(t_vault *data, char *redirection);
void	stdout_redirection(t_vault *data, char *redirection);
void	stdin_redirection(t_vault *data, char *redirection);
void	heredoc_redirection(t_vault *data);

/***** redir_in_same_array.c *****/
void	redir_in_same_array(t_vault *data, int i, int *j, char c);
void	find_redir_in_same_array(t_vault *data, char *rl_dec_array, int line,
			int j);
int		move_index_chevron(t_vault *data, int line, int i, char *rl_dec_array);
int		move_index_chevron2(t_vault *data, int line, int i, char *rl_dec_array);
int		move_index_chevron3(t_vault *data, int i, int *len, char *rl_dec_array);

/***** redir_in_same_array_2.c *****/
void	clean_redir(t_vault *data, int i);
char	*clean_redir_from_zero(t_vault *data, int i, char *str, int begin);
int		while_not_chevron(t_vault *data, int i, char *str, int *begin);
int		len_without_redir(t_vault *data, int i, int temp, int *begin);
int		len_from_chevron_at_zero(t_vault *data, int i, int *begin);

/***** redirection_utils.c *****/
char	*clean_the_chevron(t_vault *data, char *str, int line, int i);
int		flag_in_str(char *str);
int		while_is_not_flag(char *str, int i);
int		while_quote(t_vault *data, char *str, int i);

/***** redirection_utils_2.c *****/
void	dup_from_begin(t_vault *data, int i, int j, char *temp);
int		is_in_quote(t_vault *data, int line, int array);
int		return_len(t_vault *data, int i, int *temp, int len);
void	len_of_redir(t_vault *data, char *rl_dec_array, int line);
void	end_of_redir(t_vault *data, int i, int len, char *rl_dec_array);

/***** quote_management.c *****/
void	find_str_quote(t_vault *data);
void	len_of_replacement(t_vault *data, int *i);
void	begin_of_new_replacement(t_vault *data, int *rl_index);
void	len_after_quote(t_vault *data, int *rl_index);
void	space_count_update(t_vault *data, int *rl_index);

/***** quote_management_2.c *****/
void	find_decomposer_array_to_replace(t_vault *data, int end);
void	replace_decomposer_array(t_vault *data, int end, int *i);
void	find_decomposer_to_switch(t_vault *data, int to_switch);
int		check_full_space(t_vault *data, int line);

/***** built_in.c *****/
void	ft_cd(t_vault *data);
void	ft_pwd(t_vault *data);
void	ft_exit(t_vault *data);
void	ft_env(t_vault *data, int env);
void	ft_echo(t_vault *data, int line);

/***** parsing_utils ******/
void	final_quotes_removing(t_vault *data, int row);
int		quote_mngmt(t_vault *data, int line, int i, char quote);
int		check_is_redir(t_vault *data, int row, int i);
int		line_count(t_vault *data, int line);
int		quote_parsing_removal(t_vault *data, int line);

/***** built_in2.c *****/
void	ft_unset(t_vault *data, int line);
void	remove_line_env(t_vault *data, int i);
void	ft_export(t_vault *data, int line);
void	add_line_env(t_vault *data);
void	order_env(t_vault *data);

/***** error_management.c *****/
int		check_error(t_vault *data, int row);
void	error_message(t_vault *data, char *message, char *code);
char	*find_error_code(t_vault *data);
void	exit_process(t_vault *data);
void	put_code_in_fd(char *code, int fd);

/***** minishell_utils.c *****/
void	print_row(t_vault *data, int line);
int		ft_isinset(char c);
void	export_only_format(t_vault *data, char *buff2, char **temp, int i);
void	heredoc_unlink(t_vault *data);
void	execve_fail(t_vault *data);

/***** built_in_utils.c *****/
void	join_unset(t_vault *data, int line);
void	swap_lines(t_vault *data, int rows);
void	dup_env(t_vault *data);
void	var_prep(t_vault *data, int line);
void	copy_env(t_vault *data, char **temp, int i);

/***** dollar_utils.c *****/
int		dollar_var_to_expand(t_vault *data, int row, int i);
char	*var_extract(t_vault *data, int row, int position);
char	*does_var_exist(t_vault *data);
char	*expand_var(t_vault *data, int row_var);
void	copy_buffer(t_vault *data, char *temp);

/***** minus_utils. *****/
void	parse_minus(t_vault *data);
void	recreate_arg_tab(t_vault *data, char **tab);
char	**create_temp_swap(t_vault *data, int row);
void	check_minus_validity(t_vault *data, int row, int i);

/***** pipe_utils.c *****/
void	create_tab_arg(t_vault *data, int row, int line);
void	switch_lines(t_vault *data, int row, int line);
void	do_the_switch(t_vault *data, int line);
void	validate_the_switch(t_vault *data, int row, int line);
int		check_pipe_validity(t_vault *data);

/***** heredoc.c *****/
void	heredoc(t_vault *data, int i);
void	check_eof(t_vault *data, char *str);
void	reset_n_close_heredoc(t_vault *data, int line);
void	check_heredoc_active(t_vault *data, int line, int j);

/***** prog_utils.c *****/
int		find_paths(t_vault *data);
void	cmd_path_check(t_vault *data);
void	find_prog(t_vault *data, int line);
void	make_some_free(t_vault *data);
void	copy_cmd(t_vault *data, int line, int i);

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
int		prep_temp(t_vault *data, int row, int *i, int j);
void	copy_or_search_pipe(t_vault *data, int row);

/***** signal_management.c *****/
void	init_signal(int mode);
void	interrupt_alive(int sig);
void	interrupt_exec(int sig);
void	quit_exec(int sig);
//t_vault	*get_data(void);

/***** dollar_parsing_utils.c *****/
void	dollar_parsing(t_vault *data);
int		move_index(t_vault *data, int row, int i);
int		quote_parsing_with_dollar(t_vault *data, int row, int i);
int		sgl_quote_parsing(t_vault *data, int row, int i);
int		dbl_quote_parsing(t_vault *data, int row, int i);

/***** cleaning.c *****/
void	clean_before_exit(t_vault *data);
void	close_fd(t_vault *data);
void	free_struct_b_in(t_vault *data);
void	free_struct_flag(t_vault *data);

/***** redirection_utils_3.c *****/
void	clean_clean_redir(t_vault *data, int i);

/***** minishell_utils2.c *****/
void	pid_status_execve(t_vault *data);
void	good_code_format(t_vault *data);
int		check_wrong_redirection(t_vault *data);
char	*check_env_home_exist(t_vault *data);
void	change_arg_cd(t_vault *data);

/***** DEBUG *****/
int		check_if_inside_quote(char *str, char c);
void	print_double_array(char **array);
//int		dbl_array_len(char **array);

#endif