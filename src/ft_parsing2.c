/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 10:06:40 by kferterb          #+#    #+#             */
/*   Updated: 2022/04/13 10:57:58 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_parse_out_redirect_lite(t_lst *o, int *j)
{
	if (o->next->str[0] == '|' || o->next->str[0] == '<'
		|| o->next->str[0] == '>')
		return (write(2, "syntax error\n", 13), free(o->str), NULL);
	ft_check_parse(o->next);
	g_o.fd_in = open(o->next->str, O_WRONLY | O_CREAT | O_TRUNC);
	if (g_o.fd_in == -1)
		return (write(2, "error open file\n", 16), free(o->str), NULL);
	g_o.in_file_flag = 1;
	free(o->next->str);
	o->next->str = NULL;
	return (free(o->str), NULL);
}

char	*ft_parse_redirect_lite(t_lst *o, int *j, int flag)
{
	if (o->next->str[0] == '|' || o->next->str[0] == '<'
		|| o->next->str[0] == '>')
		return (write(2, "syntax error\n", 13), free(o->str), NULL);
	ft_check_parse(o->next);
	if (flag == 1)
	{
		g_o.fd_in = open(o->next->str, O_RDONLY);
		if (g_o.fd_in == -1)
			return (write(2, "error open file\n", 16), free(o->str), NULL);
		g_o.in_file_flag = 1;
	}
	else if (flag == 2)
	{
		g_o.fd_out = open(o->next->str, O_WRONLY | O_CREAT | O_TRUNC);
		if (g_o.fd_out == -1)
			return (write(2, "error open file\n", 16), free(o->str), NULL);
		g_o.out_file_flag = 1;
	}
	else if (flag == 3)
	{
		g_o.fd_re_out = open(o->next->str, O_WRONLY | O_CREAT | O_APPEND);
		if (g_o.fd_re_out == -1)
			return (write(2, "error open file\n", 16), free(o->str), NULL);
		g_o.re_out_file_flag = 1;
	}
	free(o->next->str);
	o->next->str = NULL;
	return (free(o->str), NULL);
}

char	*ft_parse_redirect(t_lst *o, int *j, int flag)
{
	int		i;
	char	*start;
	char	*end;

	if (flag == 3)
		i = *j + 2;
	else
		i = *j + 1;
	start = ft_substr(o->str, 0, *j);
	while (ft_isalnum(o->str[i]) || o->str[i] == '$'
		|| o->str[i] == '\'' || o->str[i] == '"'
		|| o->str[i] == ' ' || o->str[i] == '|')
		i++;
	end = ft_substr(o->str, i, ft_strlen(o->str));
	if (flag == 3)
		o->str = ft_substr_mod(o->str, *j + 2, i - *j - 2, 1);
	else
		o->str = ft_substr_mod(o->str, *j + 1, i - *j - 1, 1);
	if (o->str[0] == '|' || o->str[0] == '<' || o->str[0] == '>')
		return (write(2, "syntax error\n", 13), free(o->str),
			free(start), free(end), NULL);
	ft_check_parse(o);
	if (flag == 1)
	{
		g_o.fd_in = open(o->str, O_RDONLY);
		if (g_o.fd_in == -1)
			return (write(2, "error open file\n", 16), free(o->str),
				free(start), free(end), NULL);
		g_o.in_file_flag = 1;
	}
	if (flag == 2)
	{
		g_o.fd_out = open(o->str, O_WRONLY | O_CREAT | O_TRUNC);
		if (g_o.fd_out == -1)
			return (write(2, "error open file\n", 16), free(o->str),
				free(start), free(end), NULL);
		g_o.out_file_flag = 1;
	}
	if (flag == 3)
	{
		g_o.fd_re_out = open(o->str, O_WRONLY | O_CREAT | O_APPEND);
		if (g_o.fd_re_out == -1)
			return (write(2, "error open file\n", 16), free(o->str),
				free(start), free(end), NULL);
		g_o.re_out_file_flag = 1;
	}
	end = ft_sjoin(start, end, 1, 1);
	*j = -1;
	return (free(o->str), end);
}
