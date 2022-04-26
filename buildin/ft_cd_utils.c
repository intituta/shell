/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 10:45:20 by kferterb          #+#    #+#             */
/*   Updated: 2022/04/26 16:16:10 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_check_flag(int flag, int i, int k)
{
	char	*str;

	if (flag)
		str = malloc(sizeof(*str) * (i + k + 2));
	else
		str = malloc(sizeof(*str) * (i + k + 1));
	return (str);
}

char	*ft_join(char const *s1, char const *s2, int flag)
{
	size_t	i;
	size_t	k;
	size_t	n;
	char	*str;

	if (s1 == 0 || s2 == 0)
		return (NULL);
	i = ft_strlen(s1);
	k = ft_strlen(s2);
	n = 0;
	str = ft_check_flag(flag, i, k);
	if (str == 0)
		return (NULL);
	while (*s1)
		str[n++] = *s1++;
	if (flag == 1)
		str[n++] = ' ';
	if (flag == 2)
		str[n++] = '=';
	while (*s2)
		str[n++] = *s2++;
	str[n] = '\0';
	return (str);
}

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
