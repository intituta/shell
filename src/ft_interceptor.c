/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_interceptor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 12:53:52 by kferterb          #+#    #+#             */
/*   Updated: 2022/04/26 15:49:30 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_dup(t_lst *tmp, int i, int pipe_fd[2][2])
{
	if (tmp->fd_in > 0)
		dup2(tmp->fd_in, 0);
	else if (i > 0)
		dup2(pipe_fd[1][0], 0);
	if (tmp->fd_out > 0)
		dup2(tmp->fd_out, 1);
	else if (i < g_o.count_final - 1)
		dup2(pipe_fd[0][1], 1);
	close(pipe_fd[0][0]);
	close(pipe_fd[0][1]);
	ft_find_path(tmp);
}

void	ft_dup2(t_lst *tmp, int i, int pipe_fd[2][2])
{
	if (tmp->fd_in > 0)
		dup2(tmp->fd_in, 0);
	else if (i > 0)
		dup2(pipe_fd[0][0], 0);
	if (tmp->fd_out > 0)
		dup2(tmp->fd_out, 1);
	else if (i < g_o.count_final - 1)
		dup2(pipe_fd[1][1], 1);
	close(pipe_fd[0][0]);
	close(pipe_fd[1][0]);
	close(pipe_fd[1][1]);
	ft_find_path(tmp);
}

void	ft_wait(int *pid, int pipe_fd[2][2])
{
	int		i;

	i = -1;
	close(pipe_fd[0][0]);
	close(pipe_fd[1][0]);
	while (++i < g_o.count_final)
		waitpid(pid[i], &g_o.ex_code, 0);
	g_o.ex_code = WEXITSTATUS(g_o.ex_code);
	free(pid);
}

int	ft_interceptor(t_lst *tmp, int *pipe_fd)
{
	if (!ft_strcmp(tmp->execve[0], "cd"))
		return (ft_cd(tmp), 0);
	else if (!ft_strcmp(tmp->execve[0], "pwd"))
		return (ft_pwd(tmp, pipe_fd), 0);
	else if (!ft_strcmp(tmp->execve[0], "echo"))
		return (ft_echo(tmp, pipe_fd), 0);
	else if (!ft_strcmp(tmp->execve[0], "export"))
		return (ft_export(tmp, pipe_fd), 0);
	else if (!ft_strcmp(tmp->execve[0], "unset"))
		return (ft_unset(tmp), 0);
	else if (!ft_strcmp(tmp->execve[0], "env"))
		return (ft_env(tmp, pipe_fd), 0);
	else if (!ft_strcmp(tmp->execve[0], "exit"))
		if (!ft_exit(tmp))
			exit(g_o.ex_code);
	return (1);
}
