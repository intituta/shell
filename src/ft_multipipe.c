/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multipipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 10:17:18 by kferterb          #+#    #+#             */
/*   Updated: 2022/04/22 21:24:09 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

void	ft_close_multipipe(int **multipipe)
{
	int	i;

	i = -1;
	if (multipipe)
	{
		while (++i < g_o.count_final - 1)
		{
			close(multipipe[i][0]);
			close(multipipe[i][1]);
		}
		i = -1;
		while (++i < g_o.count_final - 1)
			free(multipipe[i]);
		free(multipipe);
	}
}

int	**ft_create_pipes(void)
{
	int	i;
	int	**res;

	i = -1;
	res = malloc(sizeof(int *) * g_o.count_final - 1);
	while (++i < g_o.count_final - 1)
	{
		res[i] = malloc(sizeof(int) * 2);
		pipe(res[i]);
	}
	return (res);
}

void	ft_dup(t_lst *tmp, int i, int **multipipe)
{
	if (tmp->fd_in > 0)
		dup2(tmp->fd_in, 0);
	else if (i > 0)
		dup2(multipipe[i - 1][0], 0);
	if (tmp->fd_out > 0)
		dup2(tmp->fd_out, 1);
	else if (tmp->fd_out == -2 && i < g_o.count_final - 1)
		dup2(multipipe[i][1], 1);
	close(tmp->fd_in);
	close(tmp->fd_out);
	ft_close_multipipe(multipipe);
}
