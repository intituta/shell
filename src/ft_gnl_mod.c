/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl_mod.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 10:24:22 by kferterb          #+#    #+#             */
/*   Updated: 2022/04/10 10:24:32 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_gnl(void)
{
	char	*res;
	char	*buf;

	res = NULL;
	buf = malloc(2);
	while (read(0, buf, 1) == 1 && buf[0] != '\0')
	{
		buf[1] = '\0';
		res = ft_strjoin(res, buf, 1, 0);
		if (buf[0] == '\n')
			break ;
	}
	free(buf);
	return (res);
}
