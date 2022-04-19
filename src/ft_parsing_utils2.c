/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 10:05:03 by kferterb          #+#    #+#             */
/*   Updated: 2022/04/19 12:54:16 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_find_env(char *s)
{
	char	*res;
	t_lst	*tmp;

	res = NULL;
	tmp = g_o.env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->str, s, ft_strlen(s)))
		{
			if (tmp->str[ft_strlen(s)] == '=')
				res = ft_substr(tmp->str, ft_strlen(s) + 1,
						ft_strlen(tmp->str));
		}
		tmp = tmp->next;
	}
	free(s);
	return (res);
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
	free(o->str);
	o->str = NULL;
	return (0);
}

void	ft_concatenator(t_lst *tmp, t_lst *tmp2)
{
	g_o.count++;
	tmp2->next = tmp->next;
	tmp->next = tmp2;
}

void	ft_check_list(void)
{
	int		i;
	t_lst	*tmp;

	tmp = g_o.args;
	while (tmp)
	{
		if (!ft_strcmp(tmp->str, ">>") || !ft_strcmp(tmp->str, "<<")
			|| !ft_strcmp(tmp->str, ">") || !ft_strcmp(tmp->str, "<")
			|| !ft_strcmp(tmp->str, "|"))
		{
			tmp = tmp->next;
			continue ;
		}
		i = -1;
		while (tmp->str[++i])
		{
			if (tmp->str[i] == '>' || tmp->str[i] == '<' || tmp->str[i] == '|')
				ft_put_redirect_to_list(tmp, &i);
			if (tmp->str[i] == '"')
				ft_put_quotes_to_list(tmp, &i, '"');
			if (tmp->str[i] == '\'')
				ft_put_quotes_to_list(tmp, &i, '\'');
		}
		tmp = tmp->next;
	}
}
