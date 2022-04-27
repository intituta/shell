/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_dollar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 10:05:03 by kferterb          #+#    #+#             */
/*   Updated: 2022/04/27 09:43:26 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_find_env(char *s)
{
	int		i;
	char	*res;

	i = 0;
	res = NULL;
	while (!ft_strnstr(g_o.env[i], s, ft_strlen(s)))
		if (!g_o.env[++i])
			return (free(s), NULL);
	if (g_o.env[i][ft_strlen(s)] == '=')
		res = ft_substr(g_o.env[i], ft_strlen(s) + 1,
				ft_strlen(g_o.env[i]));
	return (free(s), res);
}

char	*ft_parse_dollar(char *str, int *index)
{
	int		i;
	char	*start;
	char	*mid;
	char	*end;
	char	*res;

	i = *index;
	start = ft_substr(str, 0, i++);
	while (ft_isalpha(str[i]) || str[i] == '?')
		i++;
	mid = ft_substr(str, *index + 1, i - *index - 1);
	end = ft_substr_m(str, i, ft_strlen(str), 1);
	if (mid[0] == '?')
		mid = ft_itoa(g_o.ex_code);
	else
		mid = ft_find_env(mid);
	*index = ft_strlen(mid) - 1;
	if (!mid)
		res = ft_sjoin(start, end, 1, 1);
	else
		res = ft_sjoin(ft_sjoin(start, mid, 1, 1), end, 1, 1);
	return (res);
}
