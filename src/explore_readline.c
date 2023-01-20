/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   explore_readline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momo <momo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:55:29 by momo              #+#    #+#             */
/*   Updated: 2023/01/19 19:51:41 by momo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	explore_readline(t_vault *data)
{
	data->rl_dec = ft_split(data->read_line, ' ');
	if (data->rl_dec[0] && rl_prio_n_qty(data, 0, '\0') == TRUE
		&& check_wrong_redirection(data) == TRUE)
	{
		find_str_quote(data);
		check_for_pipe(data);
		if (pipe_check(data) == 1)
			return ;
		flag_count(data, 0, 0);
		dollar_parsing(data);
		create_tab_arg(data, -1, 0);
		if (!data->tab_arg || !(data->tab_arg[0]))
		{
			error_message(data, "putain con, regarde ce que tu ecris", "1\0");
			return ;
		}
		piping(data);
	}
	//Essayer de se rappeler pourquoi ces lignes - en les enlevant ca resoud probleme #1 du 19 janvier.
	// Parce que normalement c'est create_tab_arg qui libere rl_dec mais vue que la on passe pas dedans
	// il faut le free manuellement
	// else
	// {
	// 	ft_dbl_ptr_free((void **)data->rl_dec);
	// 	while (data->read_line[i] == ' ')
	// 		i++;
	// 	if (data->read_line[i] && data->read_line[i] != ' ')
	// 		error_message(data, "missing or wrong arguments", "1\0");
	// }
	return ;
}

void	piping(t_vault *data)
{
	int		i;

	i = 0;
	data->flag->pipe = ft_calloc(sizeof(int *), (data->flag->pipe_count) + 1);
	while (i < data->flag->pipe_count)
	{
		data->flag->pipe[i] = ft_calloc(sizeof(int), 2);
		if (pipe(data->flag->pipe[i]) == -1)
			error_message(data, "pipe creation error", "1\0");
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
	free(data->pid);
	if (data->status != 0)
		pid_status_execve(data);
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
			execute_redirection(data, line, 0);
			if (data->tab_arg[line][0] != '\0' && data->fail_redir == FALSE)
			{
				final_quotes_removing(data, line);
				data->cmd->name = ft_strdup(data->cmd->opt[0]);
				recompose_tab_arg(data, line);
				if (is_special_built_in(data, line) == TRUE)
					built_in(data, line);
				else
					forking(data, line, 1);
			}
		}
		else
			forking(data, line, 2);
		reset_io(data);
	}
	heredoc_unlink(data);
}

void	forking(t_vault *data, int line, int type)
{
	if (type == 1)
	{
		child_creation(data, line);
		if (data->pid[line] == 0)
		{
			find_prog(data, line);
			close_pipe(data);
			exit_process(data);
		}
	}
	else if (type == 2)
	{
		child_creation(data, line);
		if (data->pid[line] == 0)
		{
			dup_fds(data, line);
			execute_redirection(data, line, 0);
			if (data->tab_arg[line][0] != '\0' && data->fail_redir == FALSE)
				in_child_exec(data, line);
			close_pipe(data);
			exit_process(data);
		}
	}
}

void	child_creation(t_vault *data, int line)
{
	data->pid[line] = fork();
	if (data->pid[line] == -1)
	{
		error_message(data, "pid creation error", "1\0");
		exit_process(data);
	}
}

// À corriger :
// Gestion des fd DUO
// Gestion des leaks DUO
// Probleme de fd
// Mauvais comportement avec l'historique A DEBATTRE ERIC
// Invalid read quand ctrl + c puis echo ?$ - OK
// .tmp_error leak quand on donne une commande invalid comme : salut - OK
// invalid read avec ls | ls | ls - KO
// <test grep salut | wc -l OK
// echo salut >> file puis ctrl + D - OK
// cat + 2x ctrl-D - OK
//<test cat - Probleme de close quand test n'existe pas - OK
// echo bonjour > test | cat -e puis exit - OK
// /bin/ls - OK
// unset chocolat= puis ctrl + D - OK
// double back slash (//) leak et probleme de free
// unset PATH puis ls - OK
// "///" puis exit - OK
// echo '     ' ou "      " - OK
// "    " ou '     ' - OK
//'"' - OK
//"'" - OK
//<<> - OK
//>>< - OK
//>>> test - OK
// HEREDOC - OK
// ls | echo coucou | cat -e - OK coucou ne s'écrit pas
// ls | echo coucou - OK
// S'assurer que le .tmp_error ce créé au bon endroit et ce supprime,
//	même si on change de dossier - OK
// echo "bonjour" - OK
// ls | exit -OK
// ls | exit | ls -OK
//<< eof cat < test OK

//ls | ls | lss -la | ls $? OK

//echo coucou

//Faire des test poussé avec heredoc car j'ai un doute

//Dans l'ordre
//export test
//unset test
//export test  - OK

//Dans l'ordre
// mauvaise commande
// expr $? + $? *2  - KO (dois renvoyer 254 puis 0, )

//Dans l'ordre:
// export test
// clear -- OK

//Faire les test dans built_in2.c puis faire une commande invalid. - OK

//ctrl-c + exit ou ctrl-D - definitively lost - KO -- morgan : OK ?
//ctrl-\ pas d'erreur code envoye dans .tmp_error et pas de Quit
//	affiche dans le terminal - KO

// Si j'utilise un append et que le fichier de redirection n'existe pas,
// double free et segfault - OK

//wc - Quand on appuie sur entrée ca ne fait pas de saut de ligne - OK

//possibilite de suivre le child :
//1. ouvrir un 2e terminal
//2. lancer lldb
// lire  : https://lldb.llvm.org/use/map.html
//3a. pro at -n minishell -w
//ou 3b. pro at -p #pid
