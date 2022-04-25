/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 10:05:03 by kferterb          #+#    #+#             */
/*   Updated: 2022/04/24 19:28:12 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_find_env(char *s)
{
	int		i;
	char	*res;

	i = 0;
	res = NULL;
	while (!ft_strnstr(g_o.env[i], s, ft_strlen(s)))
		if (!g_o.env[++i])
			return (free(s), NULL);
	if (g_o.env[i][ft_strlen(s)] == '=')
		res = ft_substr(g_o.env[i], ft_strlen(s) + 1,
				ft_strlen(g_o.env[i]));
	return (free(s), res);
}

void	ft_check_parse(t_lst *o)
{
	int	i;

	i = -1;
	while (o->str[++i])
	{
		if (o->str[i] == '\'')
				o->str = ft_parse_quotes(o, &i, '\'');
		else if (o->str[i] == '"')
		{
			o->flag_meta = 1;
			o->str = ft_parse_quotes(o, &i, '"');
		}
		else if (o->str[i] == '$'
			&& (ft_isalnum(o->str[i + 1]) || o->str[i + 1] == '?'))
				o->str = ft_parse_dollar(o->str, &i);
	}
	o->flag_meta = 0;
}

int	ft_open_file(t_lst *o, int flag)
{
	if (flag == 1)
	{
		g_o.fd_in = open(o->str, O_RDONLY, O_CLOEXEC);
		if (g_o.fd_in == -1)
			return (1);
	}
	else if (flag == 2)
	{
		g_o.fd_out = open(o->str, O_WRONLY
				| O_CLOEXEC | O_TRUNC | O_CREAT, 0644);
		if (g_o.fd_out == -1)
			return (1);
	}
	else if (flag == 3)
	{
		g_o.fd_out = open(o->str, O_WRONLY
				| O_CLOEXEC | O_APPEND | O_CREAT, 0644);
		if (g_o.fd_out == -1)
			return (1);
	}
	free(o->str);
	o->str = NULL;
	return (0);
}

int	ft_check_redirects(t_lst *tmp)
{
	if (!ft_strcmp(tmp->str, "<>"))
			tmp->str = ft_substr_m(tmp->str, 1, 1, 1);
	if (!ft_strcmp(tmp->str, ">>") || !ft_strcmp(tmp->str, "<<")
		|| !ft_strcmp(tmp->str, ">") || !ft_strcmp(tmp->str, "<")
		|| !ft_strcmp(tmp->str, "|"))
		return (1);
	return (0);
}

void	ft_check_list(void)
{
	t_lst	*tmp;

	tmp = g_o.args;
	while (tmp)
	{
		if (ft_check_redirects(tmp))
		{
			tmp = tmp->next;
			continue ;
		}
		if (ft_start_preparse(tmp))
			return ;
		tmp = tmp->next;
	}
}
