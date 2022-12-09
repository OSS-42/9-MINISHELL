/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intro_minishell2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewurstei <ewurstei@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 09:00:40 by ewurstei          #+#    #+#             */
/*   Updated: 2022/12/09 09:16:51 by ewurstei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	printf("\n");
	lcyan(void);
	printf("%s\n","                   /\");
	printf("                  /  \ \n");
	printf("                 / /\ \ \n");
	printf("              /\/ /  \ \/\ \n");
	lred(void);
	printf("     /¯¯¯¯¯¯¯");
	lcyan(void);
	printf("/ / /    \ \ \ ")
	lred(void);
	printf("¯¯¯¯¯¯¯\ \n");
	lred(void);
	printf("    / \   / ");
	lcyan(void);
	printf("/ / /      \ \ \ ");
	lred(void);
	printf(" \   / \ \n");
	printf("${LRED}   /   \/  ${LCYAN}/ / /        \ \ \ ${LRED}  \/   \ ${NC}\n");
	printf("${LRED}  / \ / \ ${LCYAN}/ / /__________\ \ \ ${LRED} / \ / \ ${NC}\n");
	printf("${LRED} /___/___${LCYAN}/_/ /            \ \_\ ${LRED}___\___\ ${NC}\n");
	printf("${LCYAN}    ________/              \__${YELLOW}║${LCYAN}___${YELLOW}║${LCYAN}_ ${NC}\n");
	printf("${LCYAN}    \            ${YELLOW}         ╔══ ║   ║${LCYAN}/ ${NC}\n");
	printf("${LCYAN}       \        ${YELLOW}▀ ╔══ ║ ║ ╠═  ╚══ ╚══ ${NC}\n");
	printf("${LCYAN}    ${YELLOW}█▄ ▄█ ▀ █■■ █ ╚═╗ ╠═╣ ╚══${LCYAN}/${NC}\n");
	printf("${LCYAN}    ${YELLOW}█ ▀ █ █ █ █ █ ══╝ ║ ║ ${LCYAN}/ ${NC}\n");
	printf("${LCYAN}    ${YELLOW}█   █ █     ${LCYAN}\      / ${NC}\n");
	printf("${LCYAN}    ${YELLOW}█   █          ${LCYAN}\/ ${NC}\n");
	nc(void);
	printf("________________________________________\n");
	printf("\n");
}