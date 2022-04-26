/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 10:45:20 by kferterb          #+#    #+#             */
/*   Updated: 2022/04/26 10:46:00 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_export_add_check(char *arg)
{
	int	i;
	int	flag;

	i = -1;
	flag = 0;
	if (ft_export_error_check(arg))
		return ;
	while (arg[++i])
	{
		if (arg[i] == '=')
		{
			flag = 1;
			break ;
		}
	}
	if (flag == 0)
		return ;
	if (!g_o.env)
		return (ft_export_new_env(arg));
	ft_export_add_env(arg, i + 2);
}

int	ft_check_oldpwd(void)
{
	int	i;

	i = 0;
	while (g_o.env[i])
	{
		if (!ft_strncmp(g_o.env[i], "OLDPWD=", 8))
			return (1);
		if (!ft_strncmp(g_o.env[i], "OLDPWD=", 7))
			return (2);
		i++;
	}
	return (0);
}
