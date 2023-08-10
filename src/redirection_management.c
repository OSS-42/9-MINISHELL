/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_management.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbertin <mbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 11:10:10 by mbertin           #+#    #+#             */
/*   Updated: 2023/06/19 14:17:12 by mbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
echo test 1 > test > test1 > test2
echo test 2 >1 >2 >3
echo test 3> test> test1> test2
echo test 4>test>test1>test2>test3>test4
echo test 5>1 > 2> 3 >4 > 5
echo "test 6">"test" > "test1"
echo "test 7">"test" >"test1"
echo "test 8">"test"> "test1"> "test2"
echo "test 9">"test">"test1">"test2"
echo "test 10" > "test"> "test1" >"test2">"test3"> "test4"
echo "test 11" >test 4
echo test 12 > "tes>t"
echo test 13 > "tes>t">test1
echo test 14 > 1> 2
echo test 15 >"tes>t">test1
echo test 16>"tes>t">test1
echo "tes>t"
echo "bon>jour" ">test" >coucou

echo test 1 >> test >> test1 >> test2
echo test 2 >>1 >>2 >>3
echo test 3>> test>> test1>> test2
echo test 4>>test>>test1>>test2
echo test 5>>1 >> 2>> 3 >>4 >> 5
echo "test 6">"test" > "test1"
echo "test 7">"test" >"test1"
echo "test 8">"test"> "test1"> "test2"
echo "test 9">"test">"test1">"test2"
echo "test 10" > "test"> "test1" >"test2">"test3"> "test4"
echo "test 11" >test 4
echo test 12 > "tes>t"
echo test 13 > "tes>t">test1
echo test 14 > 1> 2
echo test 15 >"tes>t">test1
echo test 16>"tes>t">test1
echo "tes>t"
echo "bon>jour" ">test" >coucou SEGFAULT
*/

/*
	Je vais chercher un chevon qui n'est pas entre quote et le nom du
	fichier qui suit. Si le nom du fichier est dans le prochain array de
	tab_arg je rentre dans output_in_next_array.

	A partir du moment ou le fichier est trouvé et que la redirection est
	faite, je vais supprimer le chevron et le nom du fichier qui suit.
*/

void	execute_redirection(t_vault *data, int line, int j)
{
	while (data->tab_arg[line][j] && data->fail_redir == FALSE)
	{
		if (data->tab_arg[line][j] == '>' || data->tab_arg[line][j] == '<')
		{
			if (is_in_quote(data, line, j) == FALSE)
				redir_in_same_array(data, line, &j, data->tab_arg[line][j]);
		}
		j++;
	}
	heredoc_unlink(data);
}

void	redirection(t_vault *data, char *redirection)
{
	if (data->flag->chevron == '>')
		stdout_redirection(data, redirection);
	else if (data->flag->chevron == '<')
		stdin_redirection(data, redirection);
}

//mettre reset_io avec les messages d'erreur ?
void	stdout_redirection(t_vault *data, char *redirection)
{
	if (data->flag->fd_out > 0)
		close (data->flag->fd_out);
	if (data->flag->append == TRUE)
		data->flag->fd_out = open(redirection,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		data->flag->fd_out = open(redirection,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->flag->fd_out == -1)
	{
		error_message(data, "FD error", "1\0");
		data->fail_redir = TRUE;
		reset_io(data);
	}
	else if (dup2(data->flag->fd_out, STDOUT_FILENO) == -1)
	{
		error_message(data, "FD error", "1\0");
		data->fail_redir = TRUE;
		reset_io(data);
	}
	data->flag->append = FALSE;
}

//mettre reset_io avec les messages d'erreur ?
void	stdin_redirection(t_vault *data, char *redirection)
{
	if (data->flag->fd > 0)
		close (data->flag->fd);
	if (data->flag->heredoc == FALSE)
	{
		data->flag->fd = open(redirection, O_RDONLY);
		if (data->flag->fd == -1)
		{
			error_message(data, "no such file or directory", "1\0");
			data->fail_redir = TRUE;
			reset_io(data);
		}
		else
		{
			if (dup2(data->flag->fd, STDIN_FILENO) == -1)
			{
				error_message(data, "FD error (dup2)", "1\0");
				data->fail_redir = TRUE;
				reset_io(data);
			}
		}
	}
	else
		heredoc_redirection(data);
}

void	heredoc_redirection(t_vault *data)
{
	if (data->flag->heredoc == TRUE)
	{
		data->flag->heredoc_fd = open("temp_heredoc", O_RDONLY);
		if (data->flag->heredoc_fd == -1)
		{
			error_message(data, "heredoc - no such file or directory", "1\0");
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
			data->fail_redir = TRUE;
			reset_io(data);
		}
		if (dup2(data->flag->heredoc_fd, STDIN_FILENO) == -1)
		{
			error_message(data, "heredoc - I/O error (dup2)", "1\0");
			data->fail_redir = TRUE;
			reset_io(data);
		}
		data->flag->heredoc = FALSE;
		close(data->flag->heredoc_fd);
	}
}
