/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 09:17:43 by kferterb          #+#    #+#             */
/*   Updated: 2022/04/27 18:35:25 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_wait(int *pid, int pipe_fd[2][2])
{
	int		i;

	i = -1;
	close(pipe_fd[0][0]);
	close(pipe_fd[1][0]);
	while (++i < g_o.count_final)
		waitpid(pid[i], &g_o.ex_code, 0);
	if (WEXITSTATUS(g_o.ex_code))
		g_o.ex_code = WEXITSTATUS(g_o.ex_code);
	else if (WIFSIGNALED(pid[i]))
	{
		g_o.ex_code = WTERMSIG(g_o.ex_code);
		if (g_o.ex_code != 131 && g_o.ex_code != 0)
			g_o.ex_code += 128;
	}
	free(pid);
}

t_lst	*ft_first_proc(t_lst *tmp, int i, int *pid, int pipe_fd[2][2])
{
	if (tmp && !g_o.buildin_flag)
	{
		pid[i] = fork();
		if (!pid[i])
			ft_dup(tmp, i, pipe_fd);
		tmp = tmp->next;
	}
	return (tmp);
}

t_lst	*ft_second_proc(t_lst *tmp, int *i, int *pid, int pipe_fd[2][2])
{
	if (*i < g_o.count_final)
	{
		g_o.buildin_flag = 0;
		pipe(pipe_fd[1]);
		pid[*i] = fork();
		if (!pid[*i])
			ft_dup2(tmp, *i, pipe_fd);
		close(pipe_fd[0][0]);
		close(pipe_fd[1][1]);
		tmp = tmp->next;
		(*i)++;
	}
	return (tmp);
}

void	ft_exe(t_lst *tmp, int *pid, int pipe_fd[2][2])
{
	int		i;

	i = 0;
	signal(SIGINT, ft_proc_signal_handler);
	signal(SIGQUIT, ft_proc_signal_handler);
	while (i < g_o.count_final)
	{
		pipe(pipe_fd[0]);
		while (tmp)
		{
			if (!ft_interceptor(tmp, pipe_fd[0]))
			{
				tmp = tmp->next;
				continue ;
			}
			break ;
		}
		tmp = ft_first_proc(tmp, i, pid, pipe_fd);
		close(pipe_fd[0][1]);
		close(pipe_fd[1][0]);
		i++;
		tmp = ft_second_proc(tmp, &i, pid, pipe_fd);
	}
}

void	ft_multiexe(void)
{
	int		*pid;
	int		pipe_fd[2][2];
	t_lst	*tmp;

	tmp = g_o.final;
	g_o.count_final = ft_lstsize(g_o.final);
	pid = malloc(sizeof(int *) * g_o.count_final);
	ft_exe(tmp, pid, pipe_fd);
	ft_wait(pid, pipe_fd);
}
