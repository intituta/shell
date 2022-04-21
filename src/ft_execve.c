/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 16:31:26 by kferterb          #+#    #+#             */
/*   Updated: 2022/04/20 18:24:15 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	exit(0);
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

void	ft_exe(void)
{
	char	**env;
	int		pid;
	t_lst	*tmp;

	tmp = g_o.final;
	pid = fork();
	if (pid == 0)
	{
		env = ft_conv_env();
		if (tmp->fd_in > 0)
			dup2(tmp->fd_in, 0);
		if (tmp->fd_out > 0)
			dup2(tmp->fd_out, 1);
		close(tmp->fd_in);
		close(tmp->fd_out);
		ft_find_path(env, tmp);
	}
	waitpid(pid, 0, 0);
}

void	ft_execve(void)
{
	int	lst_size;

	lst_size = ft_lstsize(g_o.final);
	if (lst_size == 1)
		ft_exe();
	else
		ft_multiexe(lst_size);
}
