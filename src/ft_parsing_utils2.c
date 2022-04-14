/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 10:05:03 by kferterb          #+#    #+#             */
/*   Updated: 2022/04/14 19:04:50 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_lite(t_lst *o, int flag)
{
	if ((g_o.count > 1 && ft_strlen(o->str) == 1 && !o->flag_meta)
		|| (ft_strlen(o->str) == 2 && (o->str[1] == '<'
				|| o->str[1] == '>') && !o->flag_meta))
		return (1);
	return (0);
}

void	ft_check_flag2(int j, int flag, int i, t_lst *o)
{
	if (flag == 3)
		o->str = ft_substr_mod(o->str, j + 2, i - j - 2, 1);
	else
		o->str = ft_substr_mod(o->str, j + 1, i - j - 1, 1);
}

void	ft_check_flag(int *i, int *j, int flag)
{
	if (flag == 3)
		*i = *j + 2;
	else
		*i = *j + 1;
}

char	*ft_find_env(char *s)
{
	char	*res;
	t_lst	*tmp;

	res = NULL;
	tmp = g_o.env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->str, s, ft_strlen(s)))
		{
			if (tmp->str[ft_strlen(s)] == '=')
				res = ft_substr(tmp->str, ft_strlen(s) + 1,
						ft_strlen(tmp->str));
		}
		tmp = tmp->next;
	}
	free(s);
	return (res);
}

void	ft_check_parse(t_lst *o)
{
	int	i;

	i = -1;
	while (o->str[++i])
	{
		if (o->str[i] == '\'')
				o->str = ft_parse_quotes(o, &i, '\'');
		else if (o->str[i] == '"')
		{
			o->flag_meta = 1;
			o->str = ft_parse_quotes(o, &i, '"');
		}
		else if (o->str[i] == '$'
			&& (ft_isalnum(o->str[i + 1]) || o->str[i + 1] == '?'))
				o->str = ft_parse_dollar(o->str, &i);
	}
	o->flag_meta = 0;
}
