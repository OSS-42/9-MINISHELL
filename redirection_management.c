/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_management.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbertin <mbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 11:10:10 by mbertin           #+#    #+#             */
/*   Updated: 2022/12/21 13:33:20 by mbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
echo test 1 > test > test1 > test2
echo test 2 >1 >2 >3
echo test 3> test> test1> test2
echo test 4>test>test1>test2
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
*/

/*
	Je vais chercher un chevon qui n'est pas entre quote et le nom du
	fichier qui suit. Si le nom du fichier est dans le prochain array de
	tab_arg je rentre dans output_in_next_array.

	A partir du moment ou le fichier est trouvé et que la redirection est
	faite, je vais supprimer le chevron et le nom du fichier qui suit.
*/

void	execute_redirection(t_vault *data, int i, int j)
{
	data->flag->stdout_backup = dup(STDOUT_FILENO);
	data->flag->stdin_backup = dup(STDIN_FILENO);
	while (data->tab_arg[i] && data->tab_arg[i][0])
	{
		if ((ft_strchr(data->tab_arg[i], '>') != NULL
				&& check_if_inside_quote(data->tab_arg[i], '>') == FALSE)
			|| (ft_strchr(data->tab_arg[i], '<') != NULL
				&& check_if_inside_quote(data->tab_arg[i], '<') == FALSE))
		{
			while (data->tab_arg[i][j])
			{
				if ((data->tab_arg[i][j] == '>'
					|| data->tab_arg[i][j] == '<')
					&& (!data->tab_arg[i][j + 1] || (data->tab_arg[i][j + 1] == data->tab_arg[i][j] && !data->tab_arg[i][j + 2])))
					redir_in_next_array(data, i, &j, data->tab_arg[i][j]);
				else if (data->tab_arg[i][j] == '>'
				|| data->tab_arg[i][j] == '<')
					redir_in_same_array(data, i, &j, data->tab_arg[i][j]);
				else if (data->tab_arg[i][j] == '|' && check_if_inside_quote(data->tab_arg[i], '|') == FALSE)
					return ;
				j++;
			}
		}
		j = 0;
		i++;
	}
}

void	redirection(t_vault *data, char *redirection)
{
	if (data->flag->chevron == '>')
		stdout_redirection(data, redirection);
	else if (data->flag->chevron == '<')
		stdin_redirection(data, redirection);
}

void	stdout_redirection(t_vault *data, char *redirection)
{
	if (data->flag->fd != 0)
		close (data->flag->fd);
	if (data->flag->append == TRUE)
		data->flag->fd = open(redirection, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		data->flag->fd = open(redirection, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->flag->fd == -1)
	{
		printf("Probleme avec open sur fd_out\n");
	}
	if (dup2(data->flag->fd, STDOUT_FILENO) == -1)
	{
		printf("Probleme avec dup2 sur fd_out\n");
	}
	data->flag->append = FALSE;
}

void	stdin_redirection(t_vault *data, char *redirection)
{
	if (data->flag->fd != 0)
		close (data->flag->fd);
	data->flag->fd = open(redirection, O_RDONLY);
	if (data->flag->fd == -1)
	{
		printf("No such file or directory\n");
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else
	{
		if (dup2(data->flag->fd, STDIN_FILENO) == -1)
		{
			printf("Probleme avec dup2 sur fd_out\n");
		}
	}
}
