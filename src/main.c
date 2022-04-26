/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 16:48:33 by kferterb          #+#    #+#             */
/*   Updated: 2022/04/26 12:33:14 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_shlvl(void)
{
	int		i;
	char	*tmp;

	i = 0;
	while (!ft_strnstr(g_o.env[i], "SHLVL=", 6))
	{
		if (!g_o.env[++i])
		{
			write(2, "unset\n", 6);
			return ;
		}
	}
	tmp = g_o.env[i];
	if (ft_atoi(g_o.env[i] + 6) == 999)
		g_o.env[i] = "SHLVL=";
	else if (!ft_atoi(g_o.env[i] + 6))
		g_o.env[i] = "SHLVL=1";
	else
		g_o.env[i] = ft_sjoin("SHLVL=",
				ft_itoa(ft_atoi(g_o.env[i] + 6) + 1), 0, 1);
	free(tmp);
}

void	ft_init_env(char **env)
{
	int	i;

	i = -1;
	g_o.count_env = 0;
	while (env[g_o.count_env])
		g_o.count_env++;
	if (g_o.count_env > 0)
	{
		g_o.env = malloc(sizeof(char *) * g_o.count_env + 1);
		while (++i < g_o.count_env)
			g_o.env[i] = ft_strdup(env[i]);
		g_o.env[i] = NULL;
	}
	else
	{
		write(2, "bad_env\n", 8);
		ft_free_all();
		return ;
	}
}

void	ft_wait(int *pid, int pipe_fd[2][2])
{
	int		i;

	i = -1;
	close(pipe_fd[0][0]);
	close(pipe_fd[1][0]);
	while (++i < g_o.count_final)
		waitpid(pid[i], &g_o.ex_code, 0);
	g_o.ex_code = WEXITSTATUS(g_o.ex_code);
	free(pid);
}

void	ft_multiexe(void)
{
	int		*pid;
	int		pipe_fd[2][2];
	t_lst	*tmp;

	tmp = g_o.final;
	g_o.count_final = ft_lstsize(g_o.final);
	pid = malloc(sizeof(int *) * g_o.count_final);
	ft_exe(tmp, pid, pipe_fd);
	ft_wait(pid, pipe_fd);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	ft_check_history();
	ft_init_struct(1);
	ft_init_env(env);
	ft_shlvl();
	g_o.first = ft_create_history(NULL);
	ft_find_history();
	while (1)
	{
		ft_signals();
		g_o.input = readline(BEGIN(1, 96)"$ "CLOSE);
		if (!g_o.input)
		{
			printf("\x1B[1A\x1B[3C" "exit\n");
			break ;
		}
		if (!g_o.input[0])
		{
			free(g_o.input);
			continue ;
		}
		add_history(g_o.input);
		g_o.page = ft_create_history(g_o.input);
		ft_preparsing();
		ft_multiexe();
		ft_free_all();
	}
	ft_write_history(g_o.first);
}
