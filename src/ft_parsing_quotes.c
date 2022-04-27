/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 13:12:09 by kferterb          #+#    #+#             */
/*   Updated: 2022/04/27 09:42:37 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
