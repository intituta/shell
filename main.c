/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 16:48:33 by kferterb          #+#    #+#             */
/*   Updated: 2022/04/16 10:43:44 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_shlvl(void)
{
	t_lst	*lst;
	char	*tmp;

	lst = g_o.env;
	while (lst)
	{
		if (!ft_strncmp(lst->str, "SHLVL=", 6))
		{
			if (ft_atoi(lst->str + 6) == 999)
				lst->str = "SHLVL=";
			else if (!ft_atoi(lst->str + 6))
				lst->str = "SHLVL=1";
			else
			{
				tmp = lst->str;
				lst->str = ft_sjoin("SHLVL=",
						ft_itoa(ft_atoi(lst->str + 6) + 1), 0, 1);
				free(tmp);
			}
		}
		lst = lst->next;
	}
}

void	ft_init_env(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (!g_o.env)
			g_o.env = ft_lstnew(ft_strdup(env[i]));
		else
			ft_lstadd_back(&g_o.env, ft_lstnew(ft_strdup(env[i])));
	}
}

void	ft_init_struct(int flag)
{
	if (flag)
		g_o.env = NULL;
	g_o.input = NULL;
	g_o.fd_in = -2;
	g_o.fd_out = -2;
	g_o.pipe[0] = -2;
	g_o.pipe[1] = -2;
	g_o.count = 0;
	g_o.count_final = 0;
	g_o.split = NULL;
	g_o.final_args = NULL;
	g_o.ex_code = 0;
	g_o.final = NULL;
	g_o.args = NULL;
}

void	ft_printf(void)
{
	int		i;
	t_lst	*tmp;

	tmp = g_o.args;
	while (tmp)
	{
		printf("str = %s, meta_flag = %d\n", tmp->str, tmp->flag_meta);
		tmp = tmp->next;
	}
	tmp = g_o.final;
	while (tmp)
	{
		i = -1;
		while (tmp->execve[++i])
			printf("str-execve = %s\n", tmp->execve[i]);
		printf("----\n");
		tmp = tmp->next;
	}
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	ft_init_struct(1);
	ft_init_env(env);
	ft_shlvl();
	while (1)
	{
		ft_signals();
		g_o.input = readline("$ ");
		if (!g_o.input)
			break ;
		else if (!g_o.input[0])
		{
			free(g_o.input);
			continue ;
		}
		else
			ft_preparsing();
		if (g_o.input)
			free(g_o.input);
		ft_printf();
		ft_free_all();
	}
}
