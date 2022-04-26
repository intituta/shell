/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_add.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:41:34 by kferterb          #+#    #+#             */
/*   Updated: 2022/04/26 15:18:58 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_masslen(char **str)
{
	int	len;

	len = 0;
	if (str)
	{
		while (str[len])
			len++;
	}
	return (len);
}

void	ft_export_add_env(char *arg, int len)
{
	char	*buf;
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	buf = malloc(ft_strlen(arg));
	ft_strlcpy(buf, arg, len);
	while (g_o.env[i])
	{
		if (!ft_strncmp(g_o.env[i], buf, len - 2))
			return (ft_replace_env(arg, buf, i));
		i++;
	}
	free(buf);
	ft_export_new_env(arg);
}

void	ft_export_new_env(char *arg)
{
	char	**new_env;
	char	*str;
	int		len;

	g_o.count_env = -1;
	len = ft_masslen(g_o.env);
	new_env = malloc(sizeof(char *) * (len + 2));
	str = malloc(10000);
	ft_strlcpy(str, arg, 10000);
	while (++g_o.count_env < len)
		new_env[g_o.count_env] = g_o.env[g_o.count_env];
	new_env[len] = str;
	new_env[len + 1] = 0;
	free(g_o.env);
	g_o.env = new_env;
}

int	ft_export_error_check(char *arg)
{
	int	i;

	i = 0;
	if (!arg)
		return (1);
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalpha(arg[0]) && arg[0] != '_')
		{
			printf("export: `%s': not a valid identifier\n", arg);
			g_o.ex_code = 1;
			return (1);
		}
		if (!ft_isalnum(arg[i]) && arg[i] != '_' && arg[i] != '=')
		{
			printf("export: `%s': not a valid identifier\n", arg);
			g_o.ex_code = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_export_add(char *arg)
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
