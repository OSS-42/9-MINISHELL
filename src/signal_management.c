/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 12:04:04 by ewurstei          #+#    #+#             */
/*   Updated: 2022/12/28 17:15:30 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//manangement of ctrl+C
void	sig_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	return ;
}

//in main : signal(SIGQUIT, SIG_IGN);
//			signal(SIGINT, &sig_int);


// void	sig_int(int signal)
// {
// 	if (signal == SIGINT)
// 	{
// 		printf("\n");
// 		rl_on_new_line();
// 		rl_replace_line("", 1);
// 		rl_redisplay();
// 		g_exit_status = 1;
// 	}
// }

// void	here_sig(int signal)
// {
// 	if (signal == SIGINT)
// 	{
// 		(void)signal;
// 		g_exit_status = 1;
// 		exit(1);
// 	}
// }

// void	child_sig(int signal)
// {
// 	if (signal == SIGINT)
// 	{
// 		(void)signal;
// 		write(1, "\n", 1);
// 		g_exit_status = 130;
// 	}
// 	else if (signal == SIGQUIT)
// 	{
// 		(void)signal;
// 		write(2, "Quit: 3\n", 8);
// 		g_exit_status = 131;
// 	}
// }