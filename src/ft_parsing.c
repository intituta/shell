/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 13:40:01 by kferterb          #+#    #+#             */
/*   Updated: 2022/04/22 21:06:03 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_parse_redirect(t_lst *o, int flag, int flag2)
{
	if ((g_o.count > 1 && ft_strlen(o->str) == 1)
		|| (g_o.count > 1 && ft_strlen(o->str) == 2 && (o->str[1] == '<'
				|| o->str[1] == '>')))
		return (ft_parse_lite(o, flag, flag2));
	return (write(2, "syntax error\n", 13), ft_free_all(), NULL);
}

int	ft_check_syntax(t_lst *o)
{
	if (!o->next)
		return (1);
	if (o->next->str[0] == '|' || o->next->str[0] == '<'
		|| o->next->str[0] == '>')
		return (1);
	return (0);
}

char	*ft_parse_lite(t_lst *o, int flag, int flag2)
{
	int		i;

	i = 0;
	if (ft_check_syntax(o))
		return (write(2, "syntax error\n", 13), ft_free_all(), NULL);
	ft_check_parse(o->next);
	if (flag == 1)
	{
		ft_heredoc(o->next);
		free(o->next->str);
		o->next->str = NULL;
	}
	else if (flag == 2)
	{
		o->pipe_flag = 1;
		ft_put_list(0);
		ft_put_final_args();
		o->pipe_flag = 0;
	}
	else if (ft_open_file(o->next, flag2))
	{
		g_o.ex_code = 1;
		return (write(2, "error open\n", 13), ft_free_all(), NULL);
	}
	return (free(o->str), NULL);
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
	end = ft_substr_m(str, i, ft_strlen(str), 1);
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
	mid = ft_substr_m(o->str, *j + 1, k - *j - 1, 1);
	if (!ft_strcmp(mid, "<<") || !ft_strcmp(mid, "<")
		|| !ft_strcmp(mid, ">") || !ft_strcmp(mid, "|"))
		o->flag_meta = 1;
	if (c == '"' && ft_strchr(mid, '$') && !o->flag_meta)
		mid = find_dollar(mid);
	*j = ft_strlen(mid) - 1;
	end = ft_substr(o->str, k + 1, ft_strlen(o->str));
	return (ft_sjoin(ft_sjoin(start, mid, 1, 1), end, 1, 1));
}
