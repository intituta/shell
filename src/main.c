/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 16:48:33 by kferterb          #+#    #+#             */
/*   Updated: 2022/04/24 15:26:07 by kferterb         ###   ########.fr       */
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

void	ft_multiexe(void)
{
	int		i;
	int		*pid;
	int		pipe_fd[2][2];
	char	**env;
	t_lst	*tmp;

	tmp = g_o.final;
	g_o.count_final = ft_lstsize(g_o.final);
	pid = malloc(sizeof(int *) * g_o.count_final);
	env = ft_conv_env();
	ft_exe(tmp, pid, env, pipe_fd);
	close(pipe_fd[0][0]);
	close(pipe_fd[1][0]);
	i = -1;
	while (++i < g_o.count_final)
		waitpid(pid[i], 0, 0);
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
			ft_multiexe();
		}
		ft_free_all();
	}
}
