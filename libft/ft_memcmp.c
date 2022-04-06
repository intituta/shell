/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 13:03:53 by kferterb          #+#    #+#             */
/*   Updated: 2022/03/04 12:29:12 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *stack, const void *needle, size_t n)
{
	size_t			i;
	unsigned char	*ss1;
	unsigned char	*ss2;

	i = -1;
	ss1 = (unsigned char *)stack;
	ss2 = (unsigned char *)needle;
	while (++i < n)
		if (ss1[i] != ss2[i])
			return (ss1[i] - ss2[i]);
	return (0);
}
