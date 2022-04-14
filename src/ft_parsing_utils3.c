/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 10:06:40 by kferterb          #+#    #+#             */
/*   Updated: 2022/04/14 19:04:45 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_meta(t_lst *o, int *i)
{
	while (ft_isalnum(o->str[*i]) || o->str[*i] == '$'
		|| o->str[*i] == '\'' || o->str[*i] == '"'
		|| o->str[*i] == ' ' || o->str[*i] == '|')
		(*i)++;
}

int	ft_open_file(t_lst *o, int flag)
{
	if (flag == 1)
	{
		close(g_o.fd_in);
		g_o.fd_in = open(o->str, O_RDONLY);
		if (g_o.fd_in == -1)
			return (1);
	}
	else if (flag == 2)
	{
		close(g_o.fd_in);
		g_o.fd_out = open(o->str, O_WRONLY | O_TRUNC | O_CREAT, 0777);
		if (g_o.fd_out == -1)
			return (1);
	}
	else if (flag == 3)
	{
		close(g_o.fd_in);
		g_o.fd_out = open(o->str, O_WRONLY | O_APPEND | O_CREAT, 0777);
		if (g_o.fd_out == -1)
			return (1);
	}
	return (0);
}

void	ft_check_spase(int *j, char *mid, t_lst *o)
{
	char	*tmp;

	if ((o->next && ft_strlen(mid) == 1 && (mid[0] == '>' || mid[0] == '<'))
		|| (o->next && ft_strlen(mid) == 2 && (mid[0] == '>'
				|| mid[0] == '<' || mid[1] == '>' || mid[1] == '<')))
	{
		tmp = o->str;
		o->str = ft_sjoin(mid, o->next->str, 1, 1);
		free(tmp);
		o->next->str = NULL;
		*j = 0;
	}
}
