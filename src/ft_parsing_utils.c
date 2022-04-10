/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 09:20:55 by kferterb          #+#    #+#             */
/*   Updated: 2022/04/10 10:51:43 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_heredoc(char *limit)
{
	char	*tmp;
	char	*res;

	res = NULL;
	while (1)
	{
		write(1, "> ", 2);
		tmp = ft_gnl();
		if (ft_strcmp(tmp, limit) == 0)
			break ;
		if (!tmp)
			return (free(limit), free(res));
		res = ft_strjoin(res, tmp, 1, 1);
	}
	g_s->heredoc = res;
	free(limit);
	free(tmp);
	free(res);
}

void	ft_redirects(void)
{
	int	i;
	int	j;

	i = -1;
	while (++i < g_s->count_args)
	{
		j = -1;
		while (g_s->t_a[i].str[++j])
		{
			if (g_s->t_a[i].str[j] == '<' && g_s->t_a[i].str[j + 1] == '<')
			{
				if (ft_strlen(g_s->t_a[i].str) != 2)
					return ((void)write(2, "syntax error\n", 13));
				ft_heredoc(g_s->t_a[i + 1].str);
			}
		}
	}
}

char	*ft_find_env(char *s)
{
	int		i;
	char	*res;

	i = 0;
	s = ft_strjoin(s, "=", 1, 0);
	while (!ft_strnstr(g_s->env[i], s, ft_strlen(s)))
	{
		if (!g_s->env[++i])
			return (free(s), ft_strdup(""));
	}
	res = ft_substr(g_s->env[i], ft_strlen(s), ft_strlen(g_s->env[i]));
	return (free(s), res);
}

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


