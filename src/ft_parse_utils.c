/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 12:44:47 by kferterb          #+#    #+#             */
/*   Updated: 2022/04/06 19:54:19 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_find_env(char *s)
{
	int		i;
	char	*res;

	i = 0;
	s = ft_strjoin(s, "=", 1, 0);
	while (!ft_strnstr(g_s->env[i], s, ft_strlen(s)))
	{
		if (!g_s->env[++i])
		{
			g_s->dollar_flag++;
			res = ft_strdup("");
			return (free(s), res);
		}
	}
	res = ft_substr(g_s->env[i], ft_strlen(s), ft_strlen(g_s->env[i]));
	return (free(s), res);
}

char	*ft_parse_dollar(char *mid, int *index)
{
	int		i;
	char	*res;
	char	*start;
	char	*dollar;

	i = *index;
	start = ft_strdup(mid);
	start[i++] = '\0';
	if (start[i++] == '?')
		dollar = ft_itoa(g_s->ex_code);
	else
	{
		while (ft_isalnum(start[i]) || start[i] == '_')
			i++;
		start[i] = '\0';
		dollar = ft_find_env(ft_strdup(start + *index + 1));
	}
	res = ft_strjoin(start, dollar, 1, 1);
	*index = ft_strlen(res) - 1;
	res = ft_strjoin(res, ft_substr(mid, i, ft_strlen(mid)), 1, 1);
	return (free(mid), res);
}

char	*find_dollar(char *mid)
{
	int	i;

	i = -1;
	while (mid[++i])
		if (mid[i] == '$' && (ft_isalnum(mid[i + 1]) || mid[i + 1] == '?'))
			mid = ft_parse_dollar(mid, &i);
	return (mid);
}

char	*ft_parse_quotes(int *index, char c)
{
	int		i;
	char	*res;
	char	*mid;
	char	*start;

	i = *index;
	start = ft_strdup(g_s->in);
	start[i++] = '\0';
	while (start[i] && start[i] != c)
		i++;
	if (start[i] == '\0')
		return (write(2, "unclosed\n", 9), NULL);
	start[i++] = '\0';
	mid = ft_strdup(start + *index + 1);
	if (c == '"' && ft_strchr(mid, '$'))
		mid = find_dollar(mid);
	res = ft_strjoin(start, mid, 1, 1);
	*index = ft_strlen(res) - 1;
	res = ft_strjoin(res, ft_substr(g_s->in, i, ft_strlen(g_s->in)), 1, 1);
	return (free(g_s->in), res);
}

void	ft_parsing(void)
{
	int	i;

	i = -1;
	while (g_s->in[++i])
	{
		if (g_s->in[i] == '\'')
			g_s->in = ft_parse_quotes(&i, '\'');
		else if (g_s->in[i] == '"')
			g_s->in = ft_parse_quotes(&i, '"');
		else if (g_s->in[i] == '$'
			&& (ft_isalnum(g_s->in[i + 1]) || g_s->in[i + 1] == '?'))
				g_s->in = ft_parse_dollar(g_s->in, &i);
		if (!g_s->in)
			return ;
	}
}
