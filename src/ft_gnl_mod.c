/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl_mod.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 10:24:22 by kferterb          #+#    #+#             */
/*   Updated: 2022/04/14 14:42:30 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_heredoc(char *limit)
{
	char	*tmp;
	char	*res;

	res = NULL;
	while (1)
	{
		write(1, "> ", 2);
		tmp = ft_gnl();
		if (ft_strcmp(tmp, limit) == 0)
			break ;
		if (!tmp)
			return (free(res));
		res = ft_sjoin(res, tmp, 1, 1);
	}
	pipe(g_o.pipe);
	write(g_o.pipe[1], res, ft_strlen(res));
	g_o.fd_in = g_o.pipe[0];
	free(tmp);
	free(res);
}

char	*ft_gnl(void)
{
	char	*res;
	char	*buf;

	res = NULL;
	buf = malloc(2);
	while (read(0, buf, 1) == 1 && buf[0] != '\0')
	{
		buf[1] = '\0';
		res = ft_sjoin(res, buf, 1, 0);
		if (buf[0] == '\n')
			break ;
	}
	free(buf);
	return (res);
}
