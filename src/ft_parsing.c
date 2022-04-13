/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 13:40:01 by kferterb          #+#    #+#             */
/*   Updated: 2022/04/13 10:57:13 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_parse_heredoc_lite(t_lst *o, int *j)
{
	if (o->next->str[0] == '|' || o->next->str[0] == '<'
		|| o->next->str[0] == '>')
		return (write(2, "syntax error\n", 13), free(o->str), NULL);
	ft_check_parse(o->next);
	ft_heredoc(o->next->str);
	free(o->next->str);
	o->next->str = NULL;
	return (free(o->str), NULL);
}

char	*ft_parse_heredoc(t_lst *o, int *j)
{
	int		i;
	char	*end;
	char	*start;

	i = *j + 2;
	start = ft_substr(o->str, 0, *j);
	while (ft_isalnum(o->str[i]) || o->str[i] == '$'
		|| o->str[i] == '\'' || o->str[i] == '"'
		|| o->str[i] == ' ' || o->str[i] == '|')
		i++;
	end = ft_substr(o->str, i, ft_strlen(o->str));
	o->str = ft_substr_mod(o->str, *j + 2, i - *j - 2, 1);
	if (o->str[0] == '|' || o->str[0] == '<' || o->str[0] == '>')
		return (write(2, "syntax error\n", 13),
			free(o->str), free(start), free(end), NULL);
	ft_check_parse(o);
	ft_heredoc(o->str);
	g_o.heredoc_flag = 1;
	end = ft_sjoin(start, end, 1, 1);
	*j = -1;
	return (free(o->str), end);
}

char	*ft_parse_dollar(char *str, int *index)
{
	int		i;
	char	*start;
	char	*mid;
	char	*end;
	char	*res;

	i = *index;
	start = ft_substr(str, 0, i++);
	while (ft_isalpha(str[i]) || str[i] == '?')
		i++;
	mid = ft_substr(str, *index + 1, i - *index - 1);
	end = ft_substr_mod(str, i, ft_strlen(str), 1);
	if (mid[0] == '?')
		mid = ft_itoa(g_o.exit_code);
	else
		mid = ft_find_env(mid);
	*index = ft_strlen(mid) - 1;
	if (!mid)
		res = ft_sjoin(start, end, 1, 1);
	else
		res = ft_sjoin(ft_sjoin(start, mid, 1, 1), end, 1, 1);
	return (res);
}

char	*ft_parse_quotes(t_lst *o, int *j, char c)
{
	int		k;
	char	*start;
	char	*mid;
	char	*end;

	k = *j;
	start = ft_substr(o->str, 0, k);
	ft_check_quotes(o->str, &k, c);
	mid = ft_substr_mod(o->str, *j + 1, k - *j - 1, 1);
	if (!ft_strcmp(mid, "<<") || !ft_strcmp(mid, "<")
		|| !ft_strcmp(mid, ">") || !ft_strcmp(mid, "|"))
		o->flag_meta_symbol = 1;
	if (c == '"' && ft_strchr(mid, '$') && !o->flag_meta_symbol)
		mid = find_dollar(mid);
	*j = ft_strlen(mid) - 1;
	end = ft_substr(o->str, k + 1, ft_strlen(o->str));
	return (ft_sjoin(ft_sjoin(start, mid, 1, 1), end, 1, 1));
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
			else if (tmp->str[j] == '<' || tmp->str[j] == '>')
				tmp->str = ft_redirects(tmp, &j);
		}
		tmp = tmp->next;
	}
	return ;
}