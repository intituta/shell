/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multipipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 10:17:18 by kferterb          #+#    #+#             */
/*   Updated: 2022/04/21 09:52:25 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close_multipipe(int **multipipe, int lst_size)
{
	int	i;

	i = -1;
	if (multipipe)
	{
		while (++i < lst_size)
		{
			close(multipipe[i][0]);
			close(multipipe[i][1]);
		}
		i = -1;
		while (++i < lst_size)
			free(multipipe[i]);
		free(multipipe);
	}
}

int	**ft_create_pipes(int lst_size)
{
	int	i;
	int	**res;

	i = -1;
	res = malloc(sizeof(int *) * lst_size);
	while (++i < lst_size)
	{
		res[i] = malloc(sizeof(int) * 2);
		pipe(res[i]);
	}
	return (res);
}

void	ft_dup(t_lst *tmp, int i, int **multipipe, int lst_size)
{
	if (tmp->fd_in > 0)
		dup2(tmp->fd_in, 0);
	else if (i > 0)
		dup2(multipipe[i - 1][0], 0);
	if (tmp->fd_out > 0)
		dup2(tmp->fd_out, 1);
	else if (tmp->fd_out == -2 && i < lst_size)
		dup2(multipipe[i][1], 1);
	close(tmp->fd_in);
	close(tmp->fd_out);
	ft_close_multipipe(multipipe, lst_size - 1);
}

void	ft_multiexe(int lst_size)
{
	int		i;
	int		*pid;
	int		**pipes;
	char	**env;
	t_lst	*tmp;

	i = -1;
	tmp = g_o.final;
	pid = malloc(sizeof(int *) * lst_size);
	pipes = ft_create_pipes(lst_size - 1);
	while (tmp)
	{
		pid[++i] = fork();
		if (!pid[i])
		{
			env = ft_conv_env();
			ft_dup(tmp, i, pipes, lst_size - 1);
			ft_find_path(env, tmp);
		}
		tmp = tmp->next;
	}
	i = -1;
	while (++i < lst_size - 1)
		waitpid(pid[i], 0, 0);
	ft_close_multipipe(pipes, lst_size - 1);
}
