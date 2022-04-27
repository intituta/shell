/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 14:03:41 by kferterb          #+#    #+#             */
/*   Updated: 2022/04/26 20:19:31 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_print_env(char **env, t_lst *tmp, int *pipe)
{
	int		i;
	int		fd;
	char	**str;

	i = -1;
	fd = 1;
	ft_check_out_builtin(tmp, &fd, pipe);
	while (env[++i])
	{
		str = ft_split(env[i], '=');
		write(fd, "declare -x ", 11);
		write(fd, str[0], ft_strlen(str[0]));
		write(fd, "=", 1);
		write(fd, "\"", 1);
		write(fd, str[1], ft_strlen(str[1]));
		write(fd, "\"", 1);
		write(fd, "\n", 1);
		ft_free_mass(str);
	}
	ft_free_mass(env);
}

void	ft_swap(char **env, int i, int *flag)
{
	char	*tmp;

	tmp = env[i];
	env[i] = env[i + 1];
	env[i + 1] = tmp;
	*flag = 1;
}

void	ft_sort_env(char **env, t_lst *tmp, int *pipe)
{
	int		i;
	int		j;
	int		flag;

	flag = 1;
	while (flag == 1)
	{
		i = -1;
		flag = 0;
		while (++i < g_o.count_env - 1)
		{
			if (env[i][0] == env[i + 1][0])
			{
				j = 1;
				while (env[i][j] == env[i + 1][j])
					j++;
				if (env[i][j] && env[i + 1][j] && env[i][j] > env[i + 1][j])
					ft_swap(env, i, &flag);
			}
			else if (env[i][0] > env[i + 1][0])
				ft_swap(env, i, &flag);
		}
	}
	ft_print_env(env, tmp, pipe);
}

void	ft_export(t_lst *tmp, int *pipe)
{
	int		i;
	char	**env;

	i = -1;
	env = malloc(sizeof(char *) * g_o.count_env + 1);
	if (!tmp->execve[1])
	{
		while (g_o.env[++i])
			env[i] = ft_strdup(g_o.env[i]);
		env[i] = NULL;
		ft_sort_env(env, tmp, pipe);
	}
	else
		while (tmp->execve[++i])
			ft_export_add(tmp->execve[i]);
}
