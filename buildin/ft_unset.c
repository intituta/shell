/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 09:46:51 by kferterb          #+#    #+#             */
/*   Updated: 2022/04/26 10:00:47 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_env_tail(int i)
{
	int	flag;

	flag = 0;
	while (g_o.env[i + 1])
	{
		g_o.env[i] = g_o.env[i + 1];
		i++;
		flag = 1;
	}
	if (flag == 1)
		g_o.env[i] = 0;
}

int	ft_unset_error_check(char *arg)
{
	int	i;

	i = -1;
	while (arg[++i])
	{
		if (!ft_isalpha(arg[0]) && arg[0] != '_')
		{
			printf("unset: `%s': not a valid identifier\n", arg);
			g_o.ex_code = 1;
			return (1);
		}
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
		{
			printf("unset: `%s': not a valid identifier\n", arg);
			g_o.ex_code = 1;
			return (1);
		}
	}
	return (0);
}

void	ft_unset_env(char *arg)
{
	int		i;
	int		flag;
	char	**buf;

	i = -1;
	flag = 0;
	if (ft_unset_error_check(arg) || !g_o.env)
		return ;
	while (g_o.env[++i])
	{
		buf = ft_split(g_o.env[i], '=');
		if (!ft_strncmp(buf[0], arg, 10000))
		{
			flag = 1;
			ft_free_mass(buf);
			break ;
		}
		ft_free_mass(buf);
	}
	if (flag == 0)
		return ;
	free(g_o.env[i]);
	g_o.env[i] = 0;
	ft_env_tail(i);
}

void	ft_unset(t_lst *tmp)
{
	int	i;

	i = -1;
	while (tmp->execve[++i])
		ft_unset_env(tmp->execve[i]);
}
