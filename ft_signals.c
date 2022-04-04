/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 09:57:08 by kferterb          #+#    #+#             */
/*   Updated: 2022/04/04 10:02:35 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handler(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_redisplay();
	write(1, "  \n", 3);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_s->ex_code = 1;
}

void	ft_sig(void)
{
	struct sigaction	sa;
	sigset_t			set;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	sa.sa_handler = ft_handler;
	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sa.sa_mask = set;
	sigaction(SIGINT, &sa, NULL);
}
