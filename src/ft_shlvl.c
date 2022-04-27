/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shlvl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 13:29:04 by kferterb          #+#    #+#             */
/*   Updated: 2022/04/27 13:29:29 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**ft_join_shlvl(void)
{
	int		i;
	char	**tmp;

	i = -1;
	tmp = malloc(sizeof(char *) * g_o.count_env + 2);
	while (g_o.env[++i])
		tmp[i] = ft_strdup(g_o.env[i]);
	tmp[i++] = ft_strdup("SHLVL=1");
	tmp[i] = NULL;
	ft_free_mass(g_o.env);
	return (tmp);
}

void	ft_shlvl(void)
{
	int		i;
	char	*tmp;

	i = 0;
	while (!ft_strnstr(g_o.env[i], "SHLVL=", 6))
	{
		if (!g_o.env[++i])
		{
			g_o.env = ft_join_shlvl();
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
