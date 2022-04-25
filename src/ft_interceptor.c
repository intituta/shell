/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_interceptor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 12:53:52 by kferterb          #+#    #+#             */
/*   Updated: 2022/04/25 12:35:18 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_interceptor(t_lst *tmp)
{
	if (!ft_strcmp(tmp->execve[0], "cd"))
		return (printf("cd OK\n"), 0);
	else if (!ft_strcmp(tmp->execve[0], "pwd"))
		return (ft_pwd(), 0);
	else if (!ft_strcmp(tmp->execve[0], "echo"))
		return (printf("echo OK\n"), 0);
	else if (!ft_strcmp(tmp->execve[0], "export"))
		return (printf("export OK\n"), 0);
	else if (!ft_strcmp(tmp->execve[0], "unset"))
		return (printf("unset OK\n"), 0);
	else if (!ft_strcmp(tmp->execve[0], "env"))
		return (ft_env(), 0);
	else if (!ft_strcmp(tmp->execve[0], "exit"))
		return (printf("exit OK\n"), 0);
	return (1);
}
