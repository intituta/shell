/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_interceptor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 12:53:52 by kferterb          #+#    #+#             */
/*   Updated: 2022/04/21 13:21:18 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_interceptor(t_lst *tmp)
{
	if (!ft_strcmp(tmp->execve[0], "cd"))
	{
		printf("cd OK\n");
		exit(0);
	}
	else if (!ft_strcmp(tmp->execve[0], "pwd"))
	{
		printf("pwd OK\n");
		exit(0);
	}
	else if (!ft_strcmp(tmp->execve[0], "echo"))
	{
		printf("echo OK\n");
		exit(0);
	}
	else if (!ft_strcmp(tmp->execve[0], "export"))
	{
		printf("export OK\n");
		exit(0);
	}
	else if (!ft_strcmp(tmp->execve[0], "unset"))
	{
		printf("unset OK\n");
		exit(0);
	}
	else if (!ft_strcmp(tmp->execve[0], "env"))
	{
		printf("env OK\n");
		exit(0);
	}
	else if (!ft_strcmp(tmp->execve[0], "exit"))
	{
		printf("exit OK\n");
		exit(0);
	}
	else
		return ;
}
