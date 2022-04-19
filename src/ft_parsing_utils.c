/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 13:12:09 by kferterb          #+#    #+#             */
/*   Updated: 2022/04/19 12:59:31 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_dollar(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '$' && (ft_isalnum(str[i + 1]) || str[i + 1] == '?'))
			str = ft_parse_dollar(str, &i);
	return (str);
}

int	ft_check_quotes(char *s, int *index, char c)
{
	(*index)++;
	while (s[*index] != c)
		if (!s[++(*index)])
			return (printf("error quote\n"), 0);
	return (1);
}

char	*ft_redirects(t_lst *o, int *j)
{
	if (o->str[*j] == '<' && o->str[*j + 1] == '<')
		o->str = ft_parse_redirect(o, j, 1, 0);
	else if (o->str[*j] == '<')
		o->str = ft_parse_redirect(o, j, 0, 1);
	else if (o->str[*j] == '>' && o->str[*j + 1] == '>')
		o->str = ft_parse_redirect(o, j, 0, 3);
	else if (o->str[*j] == '>')
		o->str = ft_parse_redirect(o, j, 0, 2);
	return (o->str);
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
				tmp->str = ft_parse_redirect(tmp, &j, 2, 0);
		}
		tmp = tmp->next;
	}
	return ;
}

void	ft_preparsing(void)
{
	int	i;

	i = -1;
	add_history(g_o.input);
	g_o.split = ft_split_mod(g_o.input, ' ');
	if (!g_o.split)
		return ;
	while (g_o.split[++i])
	{
		if (!g_o.args)
			g_o.args = ft_lstnew(ft_strdup(g_o.split[i]));
		else
			ft_lstadd_back(&g_o.args, ft_lstnew(ft_strdup(g_o.split[i])));
	}
	ft_check_list();
	ft_parsing();
	ft_put_list(1);
	ft_put_final_args();
}
