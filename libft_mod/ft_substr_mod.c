/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr_mod.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 16:55:23 by kferterb          #+#    #+#             */
/*   Updated: 2022/04/21 12:12:54 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_substr_m(char *s, int start, int len, int flag)
{
	int		i;
	int		j;
	char	*res;

	if (!s)
		return (0);
	i = ft_strlen(s);
	if (i < len)
		len = i;
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	i = -1;
	j = 0;
	while (s[++i])
		if (i >= start && j < len)
			res[j++] = s[i];
	res[j] = '\0';
	if (flag)
		free(s);
	return (res);
}
