/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 13:25:39 by kferterb          #+#    #+#             */
/*   Updated: 2022/04/26 16:01:50 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_check_flag_n(t_lst *tmp, int *i, int *flag)
{
	if (!ft_strcmp(tmp->execve[1], "-n"))
	{
		*flag = 1;
		*i = 2;
	}
}

void	ft_echo(t_lst *tmp, int *pipe)
{
	int	i;
	int	fd;
	int	flag;

	fd = 1;
	ft_check_out_builtin(tmp, &fd, pipe);
	if (!tmp->execve[1])
		return ((void)write(fd, "\n", 1));
	i = 1;
	flag = 0;
	ft_check_flag_n(tmp, &i, &flag);
	while (tmp->execve[i + 1])
	{
		write(fd, tmp->execve[i], ft_strlen(tmp->execve[i]));
		write(fd, " ", 1);
		i++;
	}
	if (!flag)
		write(fd, tmp->execve[i], ft_strlen(tmp->execve[i]));
	else
		write(fd, tmp->execve[i], ft_strlen(tmp->execve[i]));
	if (!flag)
		write(fd, "\n", 1);
}
