/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 13:25:39 by kferterb          #+#    #+#             */
/*   Updated: 2022/04/26 13:39:04 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_echo(t_lst *tmp, int *pipe)
{
	int	i;
	int	fd;
	int	flag;

	fd = 1;
	ft_check_out_builtin(tmp, &fd, pipe);
	if (!g_o.final->execve[1])
		return ((void)write(fd, "\n", 1));
	i = 1;
	flag = 0;
	if (!ft_strcmp(g_o.final->execve[1], "-n"))
	{
		flag = 1;
		i = 2;
	}
	while (g_o.final->execve[i + 1])
	{
		write(fd, g_o.final->execve[i], ft_strlen(g_o.final->execve[i]));
		i++;
	}
	if (!flag)
		write(fd, g_o.final->execve[i], ft_strlen(g_o.final->execve[i]));
	else
		write(fd, g_o.final->execve[i], ft_strlen(g_o.final->execve[i]));
	if (!flag)
		write(fd, "\n", 1);
}
