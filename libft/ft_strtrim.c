/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 19:38:04 by kferterb          #+#    #+#             */
/*   Updated: 2022/04/07 10:54:13 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	cheker(char const dst, char const *src)
{
	int	i;

	i = -1;
	while (src[++i])
		if (dst == src[i])
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		end;
	int		start;
	char	*res;

	if (!s1)
		return (NULL);
	start = 0;
	while (cheker(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (start < end && cheker(s1[end - 1], set))
		end--;
	res = malloc(sizeof(*s1) * (end - start + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (start < end)
		res[i++] = s1[start++];
	res[i] = '\0';
	return (res);
}
