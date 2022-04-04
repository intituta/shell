/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 17:51:24 by kferterb          #+#    #+#             */
/*   Updated: 2022/04/03 18:22:31 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_substr(char *s, int start, int len)
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
	return (res);
}
