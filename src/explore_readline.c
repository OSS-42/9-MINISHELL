/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   explore_readline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momo <momo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:55:29 by momo              #+#    #+#             */
/*   Updated: 2022/12/23 12:00:42 by momo             ###   ########.fr       */
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
	data->debug = open("debug", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (rl_prio_n_qty(data, 0, '\0') == TRUE)
	{
		find_str_quote(data);
		flag_count(data, 0, 0);
		row_parsing(data);
		create_tab_arg(data, -1, 0);
		// execute_redirection(data, 0, 0); pour debug
		piping(data);
		reset_io(data);
		if (data->flag->fd != 0)
			close (data->flag->fd);
	}
	return ;
}

void	built_in(t_vault *data)
{
	int	i;

	i = 1;
	if (ft_strcmp("cd", data->cmd->name) == 0)
		ft_cd(data, i);
	if (ft_strcmp("pwd", data->cmd->name) == 0)
		ft_pwd(data, i);
	if (ft_strcmp("echo", data->cmd->name) == 0)
		ft_echo(data, i);
	if (ft_strcmp("env", data->cmd->name) == 0)
		ft_env (data, 1);
	if (ft_strcmp("export", data->cmd->name) == 0)
		ft_export (data, i);
	if (ft_strcmp("unset", data->cmd->name) == 0)
		ft_unset (data, i);
	if (ft_strcmp("exit", data->cmd->name) == 0)
		ft_exit (data, 0);
	return ;
}

int	is_built_in(char *str)
{
	// fprintf(stderr, "is built in\n");
	if (ft_strcmp("cd", str) == 0
		|| ft_strcmp("pwd", str) == 0
		|| ft_strcmp("echo", str) == 0
		|| ft_strcmp("env", str) == 0
		|| ft_strcmp("export", str) == 0
		|| ft_strcmp("unset", str) == 0
		|| ft_strcmp("exit", str) == 0)
		return (TRUE);
	return (FALSE);
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
		if (pipe(data->flag->pipe[i]) == -1)
			printf("Probleme de pipe\n");
		i++;
	}
	forking(data);
	i = 0;
	close_pipe(data);
	data->child_id = waitpid(0, &data->status, 0);
	data->child_id = waitpid(0, &data->status, 0);
	// while (i < data->flag->pipe_count + 1)
	// {
	// 	data->child_id = waitpid(data->pid[i], &data->status, 0);
	// 	dprintf(2, "%d\n", data->pid[i]);
	// 	i++;
	// }
}

void	forking(t_vault *data)
{
	int		line;

	line = 0;
	data->pid = ft_calloc(sizeof(int), data->flag->pipe_count + 1);
	while (data->tab_arg[line])
	{
		data->cmd->options = ft_split(data->tab_arg[line], ' ');
		data->cmd->name = ft_strdup(data->cmd->options[0]);
		if (ft_strcmp(data->cmd->name, "cd") == 0
			|| (ft_strcmp(data->cmd->name, "exit") == 0
				&& !(data->tab_arg[line + 1])))
			built_in(data);
		else
		{
			find_paths(data);
			data->pid[line] = fork();
			if (data->pid[line] != 0)
				dprintf(2, "pid : %d commande : %s\n", data->pid[line], data->cmd->name);
			if (data->pid[line] == -1)
				printf("Probleme de pid\n"); // ajouter gestion d'erreur
			else if (data->pid[line] == 0)
			{
				dup_fds(data, line);
				execute_redirection(data, 0, 0);
				find_prog(data);
				ft_exit(data, 0);
			}
		}
		line++;
	}
}

//en erreur:
//echo bonjour $USER
//echo bonjour | cat -e
//echo bonjour |cat -e

//possibilite de suivre le child :
//1. ouvrir un 2e terminal
//2. lancer lldb
// lire  : https://lldb.llvm.org/use/map.html
//3a. pro at -n minishell -w
//ou 3b. pro at -p #pid

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
