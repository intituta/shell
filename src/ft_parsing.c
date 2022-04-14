/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 13:40:01 by kferterb          #+#    #+#             */
/*   Updated: 2022/04/14 19:02:39 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_parse_redirect(t_lst *o, int *j, int flag)
{
	int		i;
	char	*start;
	char	*mid;
	char	*end;

	if (ft_check_lite(o, flag))
		return (ft_parse_lite(o, 0, flag));
	ft_check_flag(&i, j, flag);
	start = ft_substr(o->str, 0, *j);
	mid = ft_substr(o->str, *j, ft_strlen(o->str));
	ft_check_spase(j, mid, o);
	ft_check_meta(o, &i);
	end = ft_substr(o->str, i, ft_strlen(o->str));
	if (!end)
		return (free(start), o->str);
	ft_check_flag2(*j, flag, i, o);
	if (o->str[0] == '|' || o->str[0] == '<' || o->str[0] == '>' || !o->str[0])
		return (printf("error\n"), free(o->str), free(start), free(end), NULL);
	ft_check_parse(o);
	if (ft_open_file(o, flag))
		return (printf("error\n"), free(o->str), free(start), free(end), NULL);
	*j = -1;
	return (free(o->str), ft_sjoin(start, end, 1, 1));
}

char	*ft_parse_lite(t_lst *o, int flag, int flag2)
{
	int		i;
	char	*end;
	char	*tmp;

	i = 0;
	if (flag && (o->next->str[0] == '|' || o->next->str[0] == '<'
			|| o->next->str[0] == '>' || !o->next->str[0]))
		return (write(2, "syntax error\n", 13), free(o->str), NULL);
	else if (o->next->str[0] == '|' || !o->next->str[0])
		return (write(2, "syntax error\n", 13), free(o->str), NULL);
	ft_check_meta(o->next, &i);
	end = ft_substr(o->next->str, i, ft_strlen(o->next->str));
	o->next->str = ft_substr_mod(o->next->str, 0, i, 1);
	ft_check_parse(o->next);
	if (flag)
		ft_heredoc(o->next->str);
	else if (ft_open_file(o->next, flag2))
		return (write(2, "error open file\n", 13), free(o->str), NULL);
	tmp = o->next->str;
	o->next->str = ft_substr_mod(end, 0, ft_strlen(end), 1);
	return (free(tmp), free(o->str), NULL);
}

char	*ft_parse_heredoc(t_lst *o, int *j)
{
	int		i;
	char	*end;
	char	*start;

	if (g_o.count > 1 && ft_strlen(o->str) == 2 && !o->flag_meta)
		return (ft_parse_lite(o, 1, 0));
	i = *j + 2;
	start = ft_substr(o->str, 0, *j);
	ft_check_meta(o, &i);
	end = ft_substr(o->str, i, ft_strlen(o->str));
	o->str = ft_substr_mod(o->str, *j + 2, i - *j - 2, 1);
	if (o->str[0] == '|' || o->str[0] == '<' || o->str[0] == '>' || !o->str[0])
		return (write(2, "syntax error\n", 13),
			free(o->str), free(start), free(end), NULL);
	ft_check_parse(o);
	ft_heredoc(o->str);
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
		mid = ft_itoa(g_o.ex_code);
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
		o->flag_meta = 1;
	if (c == '"' && ft_strchr(mid, '$') && !o->flag_meta)
		mid = find_dollar(mid);
	*j = ft_strlen(mid) - 1;
	end = ft_substr(o->str, k + 1, ft_strlen(o->str));
	return (ft_sjoin(ft_sjoin(start, mid, 1, 1), end, 1, 1));
}
