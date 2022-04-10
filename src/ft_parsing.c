/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 13:17:04 by kferterb          #+#    #+#             */
/*   Updated: 2022/04/10 11:02:08 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_parse_dollar(char *str, int *index)
{
	int		i;
	char	*start;
	char	*mid;
	char	*res;

	i = *index;
	start = ft_strdup(str);
	start[i++] = '\0';
	if (start[i++] == '?')
		mid = ft_itoa(g_s->ex_code);
	else
	{
		while (ft_isalnum(start[i]) || start[i] == '_')
			i++;
		start[i] = '\0';
		mid = ft_find_env(ft_strdup(start + *index + 1));
	}
	res = ft_strjoin(start, mid, 1, 1);
	*index = ft_strlen(res) - 1;
	res = ft_strjoin(res, ft_substr(str, i, ft_strlen(str)), 1, 1);
	return (free(str), res);
}

char	*ft_parse_quotes(char *str, int *j, char c)
{
	int		k;
	char	*start;
	char	*mid;
	char	*end;

	k = *j;
	start = ft_substr(str, 0, k);
	ft_check_quotes(str, &k, c);
	mid = ft_substr(str, *j + 1, k - *j - 1);
	if (c == '"' && ft_strchr(mid, '$'))
		mid = find_dollar(mid);
	*j = ft_strlen(mid) - 1;
	end = ft_substr(str, k + 1, ft_strlen(str));
	return (free(str), ft_strjoin(ft_strjoin(start, mid, 1, 1), end, 1, 1));
}

void	ft_parsing(void)
{
	int	i;
	int	j;

	i = -1;
	while (++i < g_s->count_args)
	{
		j = -1;
		while (g_s->t_a[i].str[++j])
		{
			if (g_s->t_a[i].str[j] == '\'')
				g_s->t_a[i].str = ft_parse_quotes(g_s->t_a[i].str, &j, '\'');
			else if (g_s->t_a[i].str[j] == '"')
				g_s->t_a[i].str = ft_parse_quotes(g_s->t_a[i].str, &j, '"');
			else if (g_s->t_a[i].str[j] == '$'
				&& (ft_isalnum(g_s->t_a[i].str[j + 1]) || g_s->t_a[i].str[j + 1] == '?'))
					g_s->t_a[i].str = ft_parse_dollar(g_s->t_a[i].str, &j);
		}
	}
	ft_redirects();
}
