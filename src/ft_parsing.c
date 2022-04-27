/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 13:40:01 by kferterb          #+#    #+#             */
/*   Updated: 2022/04/27 10:07:07 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

void	ft_heredoc(t_lst *o)
{
	char	*tmp;
	char	*res;

	res = NULL;
	while (1)
	{
		tmp = readline("> ");
		if (ft_strcmp(tmp, o->str) == 0)
			break ;
		if (!tmp)
			return (free(res));
		if (ft_strlen(res))
			res = ft_sjoin(res, "\n", 1, 0);
		res = ft_sjoin(res, tmp, 1, 1);
	}
	res = ft_sjoin(res, "\n", 1, 0);
	pipe(g_o.pipe);
	write(g_o.pipe[1], res, ft_strlen(res));
	g_o.fd_in = g_o.pipe[0];
	close(g_o.pipe[1]);
	free(o->str);
	o->str = NULL;
	free(tmp);
	free(res);
}

void	ft_parsing(void)
{
	int		j;
	t_lst	*tmp;

	tmp = g_o.args;
	while (tmp)
	{
		j = -1;
		while (tmp->str && tmp->str[++j])
		{
			if (tmp->str[j] == '\'')
				tmp->str = ft_parse_quotes(tmp, &j, '\'');
			else if (tmp->str[j] == '"')
				tmp->str = ft_parse_quotes(tmp, &j, '"');
			else if (tmp->str[j] == '$'
				&& (ft_isalnum(tmp->str[j + 1]) || tmp->str[j + 1] == '?'))
					tmp->str = ft_parse_dollar(tmp->str, &j);
			else if (!tmp->flag_meta
				&& (tmp->str[j] == '<' || tmp->str[j] == '>'))
					tmp->str = ft_redirects(tmp, &j);
			else if (!tmp->flag_meta && tmp->str[j] == '|')
				tmp->str = ft_parse_redirect(tmp, 2, 0);
		}
		tmp = tmp->next;
	}
	return ;
}
