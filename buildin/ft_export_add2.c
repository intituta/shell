/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_add2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 17:45:28 by kferterb          #+#    #+#             */
/*   Updated: 2022/04/26 13:39:47 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_check_out_builtin(t_lst *tmp, int *fd, int *pipe)
{
	if (tmp->fd_out > 0)
	{
		*fd = tmp->fd_out;
		g_o.buildin_flag = 1;
	}
	else if (tmp->next)
	{
		*fd = pipe[1];
		g_o.buildin_flag = 1;
	}
}

void	ft_replace_env(char *arg, char *buf, int i)
{
	free(g_o.env[i]);
	ft_strlcpy(buf, arg, 10000);
	g_o.env[i] = buf;
}
