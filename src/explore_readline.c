/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   explore_readline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maison <maison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:55:29 by momo              #+#    #+#             */
/*   Updated: 2022/12/28 16:45:53 by maison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	explore_readline(t_vault *data)
{
	data->rl_dec = ft_split(data->read_line, ' ');
	if (rl_prio_n_qty(data, 0, '\0') == TRUE)
	{
		find_str_quote(data);
		flag_count(data, 0, 0);
		detached_quote_tab(data);
		check_for_pipe(data);
		row_parsing(data);
		create_tab_arg(data, -1, 0);
		piping(data);
		reset_io(data);
		if (data->flag->fd != 0)
			close (data->flag->fd);
	}
	return ;
}

//gestion d'erruer si creation de pipe en echec
void	piping(t_vault *data)
{
	int	i;

	i = 0;
	data->flag->pipe = ft_calloc(sizeof(int *), (data->flag->pipe_count) + 1);
	while (i < data->flag->pipe_count)
	{
		data->flag->pipe[i] = ft_calloc(sizeof(int), 2);
		if (pipe(data->flag->pipe[i]) == -1)
			printf("Probleme de pipe\n");
		i++;
	}
	launching_exec(data);
	i = 0;
	close_pipe(data);
	while (i < data->flag->pipe_count + 1)
	{
		data->child_id = waitpid(data->pid[i], &data->status, 0);
		i++;
	}
}

void	launching_exec(t_vault *data)
{
	int		line;

	line = -1;
	data->pid = ft_calloc(sizeof(int), data->flag->pipe_count + 1);
	while (data->tab_arg[++line] && data->tab_arg[line][0])
	{
		if (data->flag->pipe_count == 0)
		{
			execute_redirection(data, 0, 0);
			if (data->tab_arg[line][0] != '\0')
			{
				data->cmd->opt = ft_split(data->tab_arg[line], ' ');
				data->cmd->name = ft_strdup(data->cmd->opt[0]);
				recompose_tab_arg(data, line);
				if (ft_strcmp(data->cmd->name, "cd") == 0
					|| (ft_strcmp(data->cmd->name, "exit") == 0
						&& !(data->tab_arg[line + 1]))
					|| ft_strcmp(data->cmd->name, "unset") == 0
					|| ft_strcmp(data->cmd->name, "export") == 0)
					built_in(data, line);
				else
					forking(data, line, 1);
			}
		}
		else
			forking(data, line, 2);
	}
}

void	forking(t_vault *data, int line, int type)
{
	if (type == 1)
	{
		child_creation(data, line);
		if (data->pid[line] == 0)
		{
			find_prog(data, line);
			ft_exit(data, 0);
		}
	}
	else if (type == 2)
	{
		child_creation(data, line);
		if (data->pid[line] == 0)
		{
			dup_fds(data, line);
			execute_redirection(data, 0, 0);
			if (data->tab_arg[line][0] != '\0')
			{
				data->cmd->opt = ft_split(data->tab_arg[line], ' ');
				data->cmd->name = ft_strdup(data->cmd->opt[0]);
				recompose_tab_arg(data, line);
				close_pipe(data);
				find_prog(data, line);
				ft_exit(data, 0);
			}
		}
	}
}

// ajouter gestion d'erreur
void	child_creation(t_vault *data, int line)
{
	find_paths(data);
	data->pid[line] = fork();
	if (data->pid[line] == -1)
		ft_putstr_fd("Probleme de pid\n", 2);
}

//en erreur 26/12
// echo bonjour | cat -e |" wc"

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
	data->rl_dec = ft_split(data->read_line, ' ');
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
			built_in(data); (Si la commande est un built_in faire le built_in,
																sinon exeve)
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
