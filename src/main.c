/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 16:48:33 by kferterb          #+#    #+#             */
/*   Updated: 2022/04/22 10:18:14 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	g_o.args = NULL;
	g_o.final = NULL;
	g_o.split = NULL;
	g_o.count_final = 0;
	g_o.final_args = NULL;
}

void	ft_multiexe(void)
{
	int		i;
	int		*pid;
	int		**pipes;
	char	**env;
	t_lst	*tmp;

	i = -1;
	tmp = g_o.final;
	pid = malloc(sizeof(int *) * g_o.count_final);
	pipes = ft_create_pipes();
	while (tmp)
	{
		pid[++i] = fork();
		if (!pid[i])
		{
			env = ft_conv_env();
			ft_dup(tmp, i, pipes);
			ft_interceptor(tmp);
			ft_find_path(env, tmp);
		}
		tmp = tmp->next;
	}
	waitpid(pid[-1], &g_o.ex_code, 0);
	g_o.ex_code = WEXITSTATUS(g_o.ex_code);
	ft_close_multipipe(pipes);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	ft_check_history();
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
		{
			ft_preparsing();
			g_o.count_final = ft_lstsize(g_o.final);
			ft_multiexe();
		}
		ft_free_all();
	}
}
