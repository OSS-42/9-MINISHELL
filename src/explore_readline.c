/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   explore_readline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:55:29 by momo              #+#    #+#             */
/*   Updated: 2022/12/08 11:11:55 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	explore_readline(t_vault *data)
{
	// count_meta_with_space(data);
	data->rl_decomp = ft_split(data->read_line, ' ');
	// print_double_array(data->rl_decomp);
	// write(1, "\n", 1);
	if (rl_prio_n_qty(data) == TRUE)
	{
		data->rl_decomp_i = 0;
		find_str_quote(data);
		flag_count(data);
//		print_double_array(data->rl_decomp);
//		write(1, "\n", 1);
		if (data->flag->output_count > 0)
			redirection_analysiz(data);
//		print_double_array(data->rl_decomp);
//		write(1, "\n", 1);
		// if (data->flag->output_count > 0)
		// 	execute_redirection(data);
		// print_double_array(data->rl_decomp);
		// write(1, "\n", 1);
		//printf("%d\n", data->flag->output_count);
		spe_char(data, 0);
		// print_double_array(data->rl_decomp);
		// write(1, "\n", 1);
		built_in(data);
		dup2(data->flag->stdout_backup, STDOUT_FILENO);
	}
	return ;
}

//TODO Rajouter des free et autres dans les if de sécurité
void	execute_redirection(t_vault *data)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = 0;
	data->flag->fd_out = malloc(sizeof(int) * data->flag->output_count);
	data->flag->stdout_backup = dup(STDOUT_FILENO);
	while (data->rl_decomp[i] && data->rl_decomp[i][0])
	{
		if (ft_strchr(data->rl_decomp[i], '>') != NULL)
		{
			data->flag->fd_out[j] = open(data->flag->output[j],
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (data->flag->fd_out[j] == -1)
			{
				printf("Probleme avec open sur fd_out\n");
			}
			if (dup2(data->flag->fd_out[j], STDOUT_FILENO) == -1)
			{
				printf("Probleme avec dup2 sur fd_out\n");
			}
			j++;
			len = ft_strlen(data->rl_decomp[i]);
			if (data->rl_decomp[i][len - 1] == '>' && len != 1)
				data->rl_decomp[i][len - 1] = '\0';
			else
			{
				data->quote_in->spc_count = 1;
				find_decomposer_to_switch(data, i);
				i--;
			}
		}
		i++;
	}
	free(data->flag->fd_out);
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

void	count_meta_with_space(t_vault *data)
{
	int	i;

	i = 0;
	while (data->read_line[i])
	{
		if (data->read_line[i] == '>' && data->read_line[i + 1] == ' ')
			data->flag->chevron_with_space++;
		i++;
	}

}

// void	reduce_space(t_vault *data)
// {
// 	int		i;
// 	int		j;
// 	int		k;
// 	char	*temp;

// 	i = 0;
// 	j = 0;
// 	k = 0;
// 	while (data->rl_decomp[i])
// 	{
// 		temp = data->rl_decomp[i];
// 		printf("%s\n", temp);
// 		while (data->rl_decomp[i][j])
// 		{
// 			if (data->rl_decomp[i][j] == ' ')
// 				while (data->rl_decomp[i][j + 1] == ' ')
// 					j++;
// 			temp[k] = data->rl_decomp[i][j];
// 			k++;
// 			j++;
// 		}
// 		printf("%s\n", temp);
// 		k = 0;
// 		j = 0;
// 		i++;
// 	}
// }