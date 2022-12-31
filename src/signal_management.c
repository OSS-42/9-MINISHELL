/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 12:04:04 by ewurstei          #+#    #+#             */
/*   Updated: 2022/12/31 16:08:30 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_signal(int mode)
{
	if (mode == ALIVE)
	{
		signal(SIGINT, interrupt_alive);
		signal(SIGQUIT, quit_alive);
	}
	else if (mode == EXEC)
	{
		signal(SIGINT, interrupt_exec);
		signal(SIGQUIT, quit_exec);
	}
}

//INTERACTIVE - ALIVE MODE
//management of ctrl+C
void	interrupt_alive(int sig)
{
	(void)sig;
	g_error_code = 1;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	return ;
}

//management of ctrl+D
void	quit_alive(int sig)
{
	(void)sig;
	g_error_code = 1;
	rl_redisplay();
}

//CMD EXEC - EXEC MODE
//management of ctrl+C
void	interrupt_exec(int sig)
{
	(void)sig;
	g_error_code = 130;
	kill(0, 0);
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_on_new_line();
}

//management of ctrl+D
//sans singleton
void	quit_exec(int sig)
{	
	(void)sig;
	g_error_code = 131;
	kill(0, 0);
	ft_putstr_fd("Quit: 3\n", STDOUT_FILENO);
	rl_on_new_line();
}

//avec singleton

// void	quit_exec(int sig)
// {	
// 	t_vault *data;

// 	data = get_data();
// 	(void)sig;
// 	ft_putstr_fd("Quit: ", STDOUT_FILENO);
// 	ft_putnbr_fd(data->exit_code, STDOUT_FILENO);
// 	ft_putchar_fd('\n', STDOUT_FILENO);
// 	rl_on_new_line();
// 	//exit status 131
// }

// t_vault	*get_data(void)
// {
// 	static t_vault	*data = NULL;

// 	if (data == NULL)
// 		data = (t_vault *)ft_calloc(1, sizeof(t_vault));
// 	return (data);
// }
