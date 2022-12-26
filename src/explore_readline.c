/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   explore_readline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:55:29 by momo              #+#    #+#             */
/*   Updated: 2022/12/26 11:30:44 by ewurstei         ###   ########.fr       */
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
//		print_double_array(data->rl_decomp);
		create_tab_arg(data, -1, 0);
		// execute_redirection(data, 0, 0); pour debug
		piping(data);
		reset_io(data);
		if (data->flag->fd != 0)
			close (data->flag->fd);
	}
	return ;
}

void	built_in(t_vault *data, int line)
{
	if (ft_strcmp("cd", data->cmd->name) == 0)
		ft_cd(data);
	if (ft_strcmp("pwd", data->cmd->name) == 0)
		ft_pwd(data);
	if (ft_strcmp("echo", data->cmd->name) == 0)
		ft_echo(data, line);
	if (ft_strcmp("env", data->cmd->name) == 0)
		ft_env (data, 1);
	if (ft_strcmp("export", data->cmd->name) == 0)
		ft_export (data, 1);
	if (ft_strcmp("unset", data->cmd->name) == 0)
		ft_unset (data, 1);
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
	while (i < data->flag->pipe_count + 1)
	{
		data->child_id = waitpid(data->pid[i], &data->status, 0);
		i++;
	}
}

void	forking(t_vault *data)
{
	int		line;

	line = 0;
	data->pid = ft_calloc(sizeof(int), data->flag->pipe_count + 1);
	while (data->tab_arg[line] && data->tab_arg[line][0])
	{
		if (data->flag->pipe_count == 0)
		{
			execute_redirection(data, 0, 0);
			data->cmd->options = ft_split(data->tab_arg[line], ' ');
			data->cmd->name = ft_strdup(data->cmd->options[0]);
			recompose_tab_arg(data, line);
			if (ft_strcmp(data->cmd->name, "cd") == 0
				|| (ft_strcmp(data->cmd->name, "exit") == 0
					&& !(data->tab_arg[line + 1])))
				built_in(data, line);
			else
			{
				find_paths(data);
				data->pid[line] = fork();
				if (data->pid[line] == -1)
					printf("Probleme de pid\n"); // ajouter gestion d'erreur
				else if (data->pid[line] == 0)
				{
					find_prog(data, line);
					ft_exit(data, 0);
				}
			}
		}
		else
		{
			find_paths(data);
			data->pid[line] = fork();
			if (data->pid[line] == -1)
				printf("Probleme de pid\n"); // ajouter gestion d'erreur
			else if (data->pid[line] == 0)
			{
				dup_fds(data, line);
				execute_redirection(data, 0, 0);
				data->cmd->options = ft_split(data->tab_arg[line], ' ');
				data->cmd->name = ft_strdup(data->cmd->options[0]);
				recompose_tab_arg(data, line);
				close_pipe(data);
				find_prog(data, line);
				ft_exit(data, 0);
			}
		}
		line++;
	}
}

void	recompose_tab_arg(t_vault *data, int line)
{
	char	*buffer;
	int		i;

	i = 1;
	buffer = NULL;
	data->tab_arg[line] = NULL;
	if (data->cmd->options[i])
		data->tab_arg[line] = ft_strdup(data->cmd->options[i]);
	else
		return ;
	i++;
	while (data->cmd->options[i])
	{
		buffer = ft_strjoin(data->tab_arg[line], " ");
		data->tab_arg[line] = NULL;
		data->tab_arg[line] = ft_strjoin(buffer, data->cmd->options[i]);
		free (buffer);
		i++;
	}
}

//en erreur 26/12
// ?? echo bonjour $US∂R | cat -e

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
