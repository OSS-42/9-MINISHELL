/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pretty.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 00:15:03 by ewurstei          #+#    #+#             */
/*   Updated: 2022/12/17 00:17:08 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRETTY_H
# define PRETTY_H

# include <stdio.h>

/***** PRETTY *****/
/***** pretty_intro_mini.c *****/
void	intro_minishell(void);
void	intro_minishell_p2(void);
void	intro_minishell_p3(void);
void	color_reset(void);

/***** pretty_intro_daftpunk.c *****/
void	intro_daftpunk(void);
void	intro_daftpunk_p2(void);
void	intro_daftpunk_p3(void);
void	intro_daftpunk_p4(void);

/***** pretty_colors.c *****/
void	lred(void);
void	lcyan(void);
void	lyellow(void);
void	lgray(void);
void	dgray(void);

#endif

