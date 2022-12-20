/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_management.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbertin <mbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 11:10:10 by mbertin           #+#    #+#             */
/*   Updated: 2022/12/20 12:09:24 by mbertin          ###   ########.fr       */
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
	rl_decomp je rentre dans output_in_next_array.

	A partir du moment ou le fichier est trouvé et que la redirection est
	faite, je vais supprimer le chevron et le nom du fichier qui suit.
*/
void	execute_redirection(t_vault *data, int i, int j)
{
	data->flag->stdout_backup = dup(STDOUT_FILENO);
	data->flag->stdin_backup = dup(STDIN_FILENO);
	while (data->rl_decomp[i] && data->rl_decomp[i][0])
	{
		if ((ft_strchr(data->rl_decomp[i], '>') != NULL
				&& check_if_inside_quote(data->rl_decomp[i], '>') == FALSE)
			|| (ft_strchr(data->rl_decomp[i], '<') != NULL
				&& check_if_inside_quote(data->rl_decomp[i], '<') == FALSE))
		{
			while (data->rl_decomp[i][j])
			{
				if ((data->rl_decomp[i][j] == '>'
					|| data->rl_decomp[i][j] == '<')
					&& (!data->rl_decomp[i][j + 1] || (data->rl_decomp[i][j + 1] == data->rl_decomp[i][j] && !data->rl_decomp[i][j + 2])))
					redir_in_next_array(data, i, &j, data->rl_decomp[i][j]);
				else if (data->rl_decomp[i][j] == '>'
				|| data->rl_decomp[i][j] == '<')
					redir_in_same_array(data, i, &j, data->rl_decomp[i][j]);
				else if (data->rl_decomp[i][j] == '|')
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
	free (redirection);
}

void	stdout_redirection(t_vault *data, char *redirection)
{
	int	fd;

	if (data->flag->append == TRUE)
		fd = open(redirection, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(redirection, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		printf("Probleme avec open sur fd_out\n");
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		printf("Probleme avec dup2 sur fd_out\n");
	}
	data->flag->append = FALSE;
}

void	stdin_redirection(t_vault *data, char *redirection)
{
	int	fd;

	(void)data;
	fd = open(redirection, O_RDONLY);
	if (fd == -1)
	{
		printf("No such file or directory\n");
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else
	{
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			printf("Probleme avec dup2 sur fd_out\n");
		}
	}
}
