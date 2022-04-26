/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multipipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 10:17:18 by kferterb          #+#    #+#             */
/*   Updated: 2022/04/26 19:36:27 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_proc_signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		signal(SIGINT, ft_proc_signal_handler);
	}
	if (signum == SIGQUIT)
	{
		write(1, "\n", 1);
		signal(SIGQUIT, ft_proc_signal_handler);
	}
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
