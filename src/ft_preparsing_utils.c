/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_preparsing_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 09:26:48 by kferterb          #+#    #+#             */
/*   Updated: 2022/04/27 09:28:00 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_concatenator(t_lst *tmp, t_lst *tmp2)
{
	g_o.count++;
	tmp2->next = tmp->next;
	tmp->next = tmp2;
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
