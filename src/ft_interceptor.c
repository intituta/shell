/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_interceptor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 12:53:52 by kferterb          #+#    #+#             */
/*   Updated: 2022/04/26 14:07:54 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	else if (!ft_strcmp(tmp->execve[0], "exit"))
		if (!ft_exit(tmp))
			exit(g_o.ex_code);
	return (1);
}
