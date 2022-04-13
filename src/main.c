/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 16:48:33 by kferterb          #+#    #+#             */
/*   Updated: 2022/04/13 10:30:28 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_shlvl(void)
{
	t_lst	*lst;
	char	*tmp;
	char	*tmp2;

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
				tmp2 = ft_itoa(ft_atoi(lst->str + 6) + 1);
				lst->str = ft_sjoin("SHLVL=", tmp2, 0, 1);
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

void	ft_init_struct(void)
{
	g_o.fd_in = 0;
	g_o.fd_out = 0;
	g_o.fd_re_out = 0;
	g_o.in_file_flag = 0;
	g_o.out_file_flag = 0;
	g_o.re_out_file_flag = 0;
	g_o.pipe[0] = 0;
	g_o.pipe[1] = 0;
	g_o.env = NULL;
	g_o.args = NULL;
	g_o.input = NULL;
	g_o.split = NULL;
	g_o.exit_code = 0;
	g_o.heredoc_flag = 0;
}

void	ft_printf(void)
{
	t_lst	*tmp;

	tmp = g_o.args;
	while (tmp)
	{
		printf("str = %s, meta_flag = %d\n", tmp->str, tmp->flag_meta_symbol);
		tmp = tmp->next;
	}
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	ft_init_struct();
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
		ft_printf();
		ft_free_all();
	}
}
