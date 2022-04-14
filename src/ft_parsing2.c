/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 10:06:40 by kferterb          #+#    #+#             */
/*   Updated: 2022/04/14 10:36:52 by kferterb         ###   ########.fr       */
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
		g_o.fd_in = open(o->str, O_RDONLY);
		if (g_o.fd_in == -1)
			return (1);
	}
	if (flag == 2)
	{
		g_o.fd_out = open(o->str, O_WRONLY | O_TRUNC | O_CREAT, 0777);
		if (g_o.fd_out == -1)
			return (1);
	}
	if (flag == 3)
	{
		g_o.fd_out = open(o->str, O_WRONLY | O_APPEND | O_CREAT, 0777);
		if (g_o.fd_out == -1)
			return (1);
	}
	return (0);
}

char	*ft_parse_redirect_lite(t_lst *o, int *j, int flag)
{
	if (o->next->str[0] == '|' || o->next->str[0] == '<'
		|| o->next->str[0] == '>' || !o->next->str[0])
		return (write(2, "syntax error\n", 13), free(o->str), NULL);
	if (ft_open_file(o->next, flag))
		return (write(2, "error open file\n", 13), free(o->str), NULL);
	free(o->next->str);
	o->next->str = NULL;
	return (free(o->str), NULL);
}

char	*ft_parse_redirect(t_lst *o, int *j, int flag)
{
	int		i;
	char	*start;
	char	*end;

	if (g_o.count > 1 && ft_strlen(o->str) <= 2 && !o->flag_meta)
		return (ft_parse_redirect_lite(o, j, flag));
	if (flag == 3)
		i = *j + 2;
	else
		i = *j + 1;
	start = ft_substr(o->str, 0, *j);
	ft_check_meta(o, &i);
	end = ft_substr(o->str, i, ft_strlen(o->str));
	if (!end)
		return (free(start), o->str);
	if (flag == 3)
		o->str = ft_substr_mod(o->str, *j + 2, i - *j - 2, 1);
	else
		o->str = ft_substr_mod(o->str, *j + 1, i - *j - 1, 1);
	if (o->str[0] == '|' || o->str[0] == '<' || o->str[0] == '>' || !o->str[0])
		return (write(2, "syntax error\n", 13), free(o->str),
			free(start), free(end), NULL);
	ft_check_parse(o);
	if (ft_open_file(o, flag))
		return (write(2, "error open file\n", 16), free(o->str),
			free(start), free(end), NULL);
	end = ft_sjoin(start, end, 1, 1);
	*j = -1;
	return (free(o->str), end);
}
