/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multipipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 10:17:18 by kferterb          #+#    #+#             */
/*   Updated: 2022/04/24 15:30:15 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_dup(t_lst *tmp, int i, char **env, int pipe_fd[2][2])
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
	ft_find_path(env, tmp);
}

void	ft_dup2(t_lst *tmp, int i, char **env, int pipe_fd[2][2])
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
	ft_find_path(env, tmp);
}

void	ft_exe(t_lst *tmp, int *pid, char **env, int pipe_fd[2][2])
{
	int		i;

	i = 0;
	while (i < g_o.count_final)
	{
		pipe(pipe_fd[0]);
		pid[i] = fork();
		if (!pid[i])
			ft_dup(tmp, i, env, pipe_fd);
		close(pipe_fd[0][1]);
		close(pipe_fd[1][0]);
		tmp = tmp->next;
		i++;
		if (i < g_o.count_final)
		{
			pipe(pipe_fd[1]);
			pid[i] = fork();
			if (!pid[i])
				ft_dup2(tmp, i, env, pipe_fd);
			close(pipe_fd[0][0]);
			close(pipe_fd[1][1]);
			tmp = tmp->next;
			i++;
		}
	}
}

char	*ft_find_path(char **env, t_lst *tmp)
{
	int	i;
	int	k;

	i = 0;
	k = -1;
	while (ft_strnstr(env[i], "PATH=", 5) == NULL)
		if (env[++i] == NULL)
			return (write(1, "error: unset path\n", 18), ft_free_all(), NULL);
	execve(ft_split(tmp->execve[0], ' ')[0], tmp->execve, env);
	while (ft_split(env[i] + 5, ':')[++k])
		execve(ft_strjoin(ft_strjoin(ft_split(env[i] + 5, ':')[k], "/"),
				tmp->execve[0]), tmp->execve, env);
	write(2, tmp->execve[0], ft_strlen(tmp->execve[0]));
	write(2, ": cmd not found\n", 16);
	ft_free_all();
	exit(127);
}

char	**ft_conv_env(void)
{
	int		count;
	char	**env;
	t_lst	*tmp;

	count = 0;
	tmp = g_o.env;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	env = malloc(sizeof(char *) * count + 1);
	tmp = g_o.env;
	count = 0;
	while (tmp)
	{
		env[count++] = ft_strdup(tmp->str);
		tmp = tmp->next;
	}
	env[count] = NULL;
	return (env);
}
