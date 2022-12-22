/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   explore_readline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbertin <mbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:55:29 by momo              #+#    #+#             */
/*   Updated: 2022/12/22 10:53:58 by mbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	row_parsing(t_vault *data)
{
	int	row;

	row = 0;
	data->b_in->forget_minus = 0;
	data->b_in->minus_n = 0;
	data->b_in->dont_do_minus = 0;
	while (data->rl_decomp[row] && data->rl_decomp[row][0])
	{
		data->buffer = ft_calloc(sizeof(char), 500);
		quote_priority(data, row);
		parse_row(data, row);
		free(data->buffer);
		data->b_in->forget_minus = 0;
		data->b_in->echo_first = 0;
		row++;
	}
}

void	explore_readline(t_vault *data)
{
	data->rl_decomp = ft_split(data->read_line, ' ');
	if (rl_prio_n_qty(data, 0, '\0') == TRUE)
	{
		find_str_quote(data);
		flag_count(data, 0, 0);
		execute_redirection(data, 0, 0);
		row_parsing(data);
		create_tab_arg(data, -1, 0);
		piping(data);
		built_in(data);
		forking()
		dup2(data->flag->stdout_backup, STDOUT_FILENO);
		dup2(data->flag->stdin_backup, STDIN_FILENO);
		close (data->flag->stdout_backup);
		close (data->flag->stdin_backup);
		if (data->flag->fd != 0)
			close (data->flag->fd);
	}
	return ;
}

void	built_in(t_vault *data)
{
	int	i;

	i = 1;
	if (ft_strcmp("cd", data->rl_decomp[0]) == 0)
		ft_cd(data, i);
	if (ft_strcmp("pwd", data->rl_decomp[0]) == 0)
		ft_pwd(data, i);
	if (ft_strcmp("echo", data->rl_decomp[0]) == 0)
		ft_echo(data, i);
	if (ft_strcmp("env", data->rl_decomp[0]) == 0)
		ft_env (data, 1);
	if (ft_strcmp("export", data->rl_decomp[0]) == 0)
		ft_export (data, i);
	if (ft_strcmp("unset", data->rl_decomp[0]) == 0)
		ft_unset (data, i);
	if (ft_strcmp("exit", data->rl_decomp[0]) == 0)
		ft_exit (data);
	return ;
}

void	piping(t_vault *data)
{
	int	i;

	i = 0;
	data->flag->pipe = ft_calloc(sizeof(int *), (data->flag->pipe_count));
	// if (!data->flag->pipe)
		// Gestion d'erreur
	while (i < data->flag->pipe_count)
	{
		data->flag->pipe[i] = ft_calloc(sizeof(int), 2);
		// if (pipe(data->pipe[i]) == -1)
		// 	Gestion d'erreur
		i++;
	}
}

void	forking(t_vault *data)
{
	int		i;
	int		line;
	i = 0;
	line = 0;

	while (data-> tab_arg[i])
	{
		data->pid = fork();
		if (data->pid == -1)
			printf("Probleme de pid\n"); // ajouter gestion d'erreur
		else if (data->pid == 0)
		{
			check_redirection(data);
			close_pipe(data);
			check_access(data, j);
			exit(EXIT_FAILURE);
		}
		data->fork_count++;
		j++;
	}
}

void	check_redirection(t_vault *data)
{
	if (data->fork_count == 0)
	{
		redirect_pipe(data->fd_in, data->flag->pipe[0][1]);
		close(data->fd_in);
	}
	else if (data->fork_count + 1 < data->cmd_count)
		redirection(data->pipe[data->fork_count - 1][0],
			data->pipe[data->fork_count][1]);
	else if (data->fork_count == data->cmd_count - 1)
	{
		check_fd(data, data->argv, "fd_out");
		redirection(data->pipe[data->fork_count - 1][0], data->fd_out);
		close(data->fd_out);
	}
}

void	redirect_pipe(int input, int output)
{
	if (dup2(input, STDIN_FILENO) == -1)
	{
		write(2, "Error dup STDIN\n", 16);
		exit (1);
	}
	if (dup2(output, STDOUT_FILENO) == -1)
	{
		write(2, "Error dup STDOUT\n", 16);
		exit (1);
	}
}
/*
	Si la commande est un exit mais qu'elle est suivi d'un pipe, il faut
	executer exit dans un child process. Sinon si exit est la seul commande
	il faut l'executer dans le parents.

	void	explore_readline(t_vault *data)
{
	data->rl_decomp = ft_split(data->read_line, ' ');
	if (rl_prio_n_qty(data, 0, '\0') == TRUE)
	{
		find_str_quote(data);
		flag_count(data, 0, 0);
		row_parsing(data);
		create_tab_arg(data, -1, 0);
		piping (compter, créer, relier les pipes)
		while (tab_arg[i]) (dans une fonction forking)
		{
			redirection_management;
			close_pipe
			find_path (rajouter une condition pour voir si c'est un built_in)
			built_in(data); (Si la commande est un built_in faire le built_in, sinon exeve)
		}
		dup2(data->flag->stdout_backup, STDOUT_FILENO);
		dup2(data->flag->stdin_backup, STDIN_FILENO);
		close (data->flag->stdout_backup);
		close (data->flag->stdin_backup);
		if (data->flag->fd != 0)
			close (data->flag->fd);
	}
	return ;
}
*/