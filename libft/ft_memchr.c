/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 12:18:48 by kferterb          #+#    #+#             */
/*   Updated: 2022/03/04 12:29:10 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ss;

	i = -1;
	ss = (unsigned char *)s;
	if (n == 0)
		return (NULL);
	while (++i < n)
		if (ss[i] == (unsigned char)c)
			return (&ss[i]);
	return (0);
}
