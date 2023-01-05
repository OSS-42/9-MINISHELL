/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbertin <mbertin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 23:09:55 by ewurstei          #+#    #+#             */
/*   Updated: 2023/01/05 10:29:38 by mbertin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_row(t_vault *data, int line)
{
	if ((data->b_in->echo_flag_n == 1 && data->b_in->forget_minus == 0))
	{
		ft_putstr_fd(data->tab_arg[line], 1);
		data->b_in->first_word = 0;
	}
	else if (data->b_in->first_word == 1)
	{
		ft_putstr_fd(data->tab_arg[line], 1);
		data->b_in->first_word = 0;
	}
	else
	{
		ft_putstr_fd(" ", 1);
		ft_putstr_fd(data->tab_arg[line], 1);
	}
	return ;
}

int	ft_isinset(char c)
{
	if (c == '\'')
		return (1);
	else if (c == '\"')
		return (2);
	else if (c == '$')
		return (3);
	else
		return (0);
}

void	export_only_format(t_vault *data, char *buff2, char **temp, int i)
{
	data->buffer = ft_strjoin("declare -x ", temp[i]);
	free (temp[i]);
	temp[i] = ft_strdup(data->buffer);
	free (data->buffer);
	data->buffer = ft_strjoin(temp[i], "\"");
	free (temp[i]);
	temp[i] = ft_strdup(data->buffer);
	free (data->buffer);
	buff2 = ft_strtrim(ft_strchr(data->env[i], '='), "=");
	data->buffer = ft_strjoin(temp[i], buff2);
	free (buff2);
	free (temp[i]);
	temp[i] = ft_strdup(data->buffer);
	free (data->buffer);
	data->buffer = ft_strjoin(temp[i], "\"");
	free (temp[i]);
	temp[i] = ft_strdup(data->buffer);
	free (data->buffer);
}

void	clean_before_exit(t_vault *data)
{
	if (data->b_in->export_var)
		free (data->b_in->export_var);
	if (data->b_in->env_export)
		ft_dbl_ptr_free((void **)data->b_in->env_export);
	if (data->b_in->env_unset)
		ft_dbl_ptr_free((void **)data->b_in->env_unset);
	if (data->b_in->env_ord)
		free(data->b_in->env_ord);
	if (data->read_line)
		free(data->read_line);
	if (data->tab_arg)
		ft_dbl_ptr_free((void **)data->tab_arg);
	if (data->cmd->opt)
		ft_dbl_ptr_free((void **)data->cmd->opt);
	if (data->pid)
		free (data->pid);
	if (data->flag->pipe)
		free (data->flag->pipe);
	free(data->cmd->name);
	free (data->cmd);
	close (data->flag->stdin_backup);
	close (data->flag->stdout_backup);
	if (data->b_in)
		free(data->b_in);
	if (data->quote)
		free(data->quote);
	if (data->flag)
		free(data->flag);
}

// l:88 : Que ce free soit la ou pas j'ai les mêmes leaks ...
// free (data->b_in); //
// free (data->quote);
// free (data->flag);

void	heredoc_unlink(t_vault *data)
{
	if (data->flag->heredoc == TRUE)
	{
		data->flag->heredoc = FALSE;
		unlink("temp_heredoc");
	}
}
