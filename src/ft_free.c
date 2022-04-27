/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 20:17:59 by kferterb          #+#    #+#             */
/*   Updated: 2022/04/27 10:42:21 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_history(void)
{
	t_log	*page;
	char	*buf;

	while (g_o.first)
	{
		page = g_o.first;
		buf = g_o.first->data;
		g_o.first = g_o.first->next;
		free (buf);
		free (page);
	}
}

void	ft_free_mass(char **str)
{
	int		i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
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
	while (g_o.split && g_o.split[++i])
		free(g_o.split[i]);
	free(g_o.split);
	ft_free_struct(g_o.args);
	ft_free_struct(g_o.final);
	ft_init_struct(0);
}
