/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 10:17:18 by kferterb          #+#    #+#             */
/*   Updated: 2022/04/27 09:21:06 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_get_path(t_lst *tmp, int i)
{
	int		j;
	char	*path;
	char	**strs;

	j = -1;
	strs = ft_split(g_o.env[i] + 5, ':');
	while (strs[++j])
	{
		path = ft_strjoin(strs[j], "/");
		path = ft_sjoin(path, tmp->execve[0], 1, 0);
		if (!access(path, F_OK))
		{
			j = -1;
			while (strs[++j])
				free(strs[j]);
			free(strs);
			execve(path, tmp->execve, g_o.env);
		}
		free(path);
	}
	j = -1;
	while (strs[++j])
		free(strs[j]);
	free(strs);
}

char	*ft_find_path(t_lst *tmp)
{
	int		i;

	i = 0;
	signal(SIGTSTP, SIG_DFL);
	while (ft_strnstr(g_o.env[i], "PATH=", 5) == NULL)
		if (g_o.env[++i] == NULL)
			return (write(1, "error: unset path\n", 18), ft_free_all(), NULL);
	execve(ft_split(tmp->execve[0], ' ')[0], tmp->execve, g_o.env);
	ft_get_path(tmp, i);
	write(2, tmp->execve[0], ft_strlen(tmp->execve[0]));
	if (ft_strcmp(tmp->execve[0], "exit"))
		write(2, ": cmd not found\n", 16);
	else
		write(1, "\n", 1);
	ft_free_all();
	exit(127);
}

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
	return (1);
}
