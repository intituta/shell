/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 19:39:44 by kferterb          #+#    #+#             */
/*   Updated: 2022/03/04 12:29:18 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (dst == src)
		return (dst);
	if (dst <= src)
	{
		i = -1;
		while (++i < len)
			((char *) dst)[i] = ((char *) src)[i];
	}
	else
	{
		while (len > 0)
		{
			((char *) dst)[len - 1] = ((char *) src)[len - 1];
			len--;
		}
	}
	return (dst);
}
