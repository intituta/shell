/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 12:38:13 by kferterb          #+#    #+#             */
/*   Updated: 2022/04/24 19:25:47 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_init_struct(int flag)
{
	if (flag)
		g_o.env = NULL;
	g_o.input = NULL;
	g_o.fd_in = -2;
	g_o.fd_out = -2;
	g_o.pipe[0] = -2;
	g_o.pipe[1] = -2;
	g_o.count = 0;
	g_o.args = NULL;
	g_o.final = NULL;
	g_o.split = NULL;
	g_o.count_final = 0;
	g_o.final_args = NULL;
}

void	ft_free_struct(t_lst *s)
{
	int		i;
	t_lst	*tmp;

	i = -1;
	tmp = s;
	while (tmp)
	{
		i = -1;
		while (tmp->execve && tmp->execve[++i])
			free(tmp->execve[i]);
		free(tmp->execve);
		free(tmp->str);
		tmp->str = NULL;
		free(tmp);
		tmp = tmp->next;
	}
}

void	ft_free_all(void)
{
	int		i;

	i = -1;
	close(g_o.pipe[0]);
	close(g_o.pipe[1]);
	close(g_o.fd_in);
	close(g_o.fd_out);
	if (g_o.input)
		free(g_o.input);
	while (g_o.split && g_o.split[++i])
		free(g_o.split[i]);
	free(g_o.split);
	ft_free_struct(g_o.args);
	ft_free_struct(g_o.final);
	ft_init_struct(0);
}

void	ft_handler(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_redisplay();
	write(1, "  \n", 3);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_o.ex_code = 1;
}

void	ft_signals(void)
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
