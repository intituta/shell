/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 16:48:33 by kferterb          #+#    #+#             */
/*   Updated: 2022/04/10 11:00:03 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_start(void)
{
	int	i;

	i = -1;
	add_history(g_s->in);
	g_s->str = ft_split_mod(g_s->in, ' ');
	if (!g_s->str)
		return ;
	g_s->t_a = malloc(sizeof(t_args) * g_s->count_args);
	while (g_s->str[++i])
		g_s->t_a[i].str = g_s->str[i];
	ft_parsing();
	//for(int i = 0; i < g_s->count_args; i++)
	//	printf("%s\n", g_s->t_a[i].str);

}

void	ft_shlvl(void)
{
	int		i;
	char	*tmp;
	char	*res;

	i = 0;
	while (ft_strncmp(g_s->env[i], "SHLVL=", 6))
		if (!g_s->env[++i])
			exit(write(2, "unset\n", 6));
	tmp = g_s->env[i];
	if (ft_atoi(g_s->env[i] + 6) == 999)
		g_s->env[i] = "SHLVL=";
	else if (!ft_atoi(g_s->env[i] + 6))
		g_s->env[i] = "SHLVL=1";
	else
	{
		res = ft_itoa(ft_atoi(g_s->env[i] + 6) + 1);
		g_s->env[i] = ft_strjoin("SHLVL=", res, 0, 1);
	}
	free(tmp);
}

void	ft_init_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	g_s->env = malloc(sizeof(char *) * i + 1);
	i = -1;
	while (env[++i])
		g_s->env[i] = ft_substr(env[i], 0, ft_strlen(env[i]));
	g_s->env[i] = NULL;
}

void	ft_init_struct(void)
{
	g_s = malloc(sizeof(t_s));
	g_s->in = NULL;
	g_s->str = NULL;
	g_s->env = NULL;
	g_s->t_a = NULL;
	g_s->ex_code = 0;
	g_s->count_args = 0;
	g_s->heredoc = NULL;
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
		ft_sig();
		g_s->in = readline("$ ");
		if (!g_s->in)
			break ;
		else if (!g_s->in[0])
			continue ;
		else
			ft_start();
		if (g_s->in)
			free(g_s->in);
		free(g_s->heredoc);
	}
}
