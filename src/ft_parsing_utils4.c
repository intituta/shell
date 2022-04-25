/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_utils4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 13:45:14 by kferterb          #+#    #+#             */
/*   Updated: 2022/04/24 19:30:52 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

int	ft_start_preparse(t_lst *tmp)
{
	int	i;

	i = -1;
	while (tmp->str[++i])
	{
		if (tmp->str[i] == '\'')
			if (!ft_check_quotes(tmp->str, &i, '\''))
				return (1);
		if (tmp->str[i] == '"')
			if (!ft_check_quotes(tmp->str, &i, '"'))
				return (1);
		if (tmp->str[i] == '>' && tmp->str[i + 1] == '<')
			return (write(2, "syntax error\n", 13), ft_free_all(), 1);
		if (tmp->str[i] == '>' || tmp->str[i] == '<' || tmp->str[i] == '|')
			ft_put_redirect_to_list(tmp, &i);
	}
	return (0);
}

void	ft_else(t_lst *tmp, int *i)
{
	t_lst	*tmp2;

	if ((tmp->str[*i] == '<' && tmp->str[*i + 1] == '>')
		|| (tmp->str[*i] == '>' && tmp->str[*i + 1] == '<'))
	{
		(*i)++;
		tmp2 = ft_lstnew(ft_substr(tmp->str, *i + 1, ft_strlen(tmp->str)));
		tmp->str = ft_substr_m(tmp->str, 1, (*i)++, 1);
	}
	else if ((tmp->str[*i] != '|' && tmp->str[*i + 1] == '>')
		|| (tmp->str[*i] != '|' && tmp->str[*i + 1] == '<'))
	{
		tmp2 = ft_lstnew(ft_substr(tmp->str, *i + 2, ft_strlen(tmp->str)));
		tmp->str = ft_substr_m(tmp->str, 0, (*i)++ + 2, 1);
	}
	else
	{
		tmp2 = ft_lstnew(ft_substr(tmp->str, *i + 1, ft_strlen(tmp->str)));
		tmp->str = ft_substr_m(tmp->str, 0, *i + 1, 1);
	}
	ft_concatenator(tmp, tmp2);
}

void	ft_if(t_lst *tmp, char *start, int *i)
{
	t_lst	*tmp2;

	if ((tmp->str[*i] == '<' && tmp->str[*i + 1] == '>')
		|| (tmp->str[*i] == '>' && tmp->str[*i + 1] == '<'))
		tmp2 = ft_lstnew(ft_substr_m(tmp->str, ++(*i), ft_strlen(tmp->str), 1));
	else
		tmp2 = ft_lstnew(ft_substr_m(tmp->str, (*i)++, ft_strlen(tmp->str), 1));
	tmp->str = ft_substr_m(start, 0, ft_strlen(start), 1);
	ft_concatenator(tmp, tmp2);
}

void	ft_put_redirect_to_list(t_lst *tmp, int *i)
{
	char	*start;

	start = ft_substr(tmp->str, 0, *i);
	if (ft_strlen(start) > 0)
	{
		ft_if(tmp, start, i);
		*i = 0;
	}
	else
	{
		free(start);
		ft_else(tmp, i);
	}
}
