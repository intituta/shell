/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_preparsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 09:24:23 by kferterb          #+#    #+#             */
/*   Updated: 2022/04/27 10:43:48 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_start_preparse(t_lst *tmp)
{
	int	i;

	i = -1;
	while (tmp->str[++i])
	{
		if (tmp->str[i] == '\'')
			if (!ft_check_quotes(tmp->str, &i, '\''))
				return (1);
		if (tmp->str[i] == '"')
			if (!ft_check_quotes(tmp->str, &i, '"'))
				return (1);
		if (tmp->str[i] == '>' && tmp->str[i + 1] == '<')
			return (write(2, "syntax error\n", 13), ft_free_all(), 1);
		if (tmp->str[i] == '>' || tmp->str[i] == '<' || tmp->str[i] == '|')
			ft_put_redirect_to_list(tmp, &i);
	}
	return (0);
}

int	ft_check_redirects(t_lst *tmp)
{
	if (!ft_strcmp(tmp->str, "<>"))
			tmp->str = ft_substr_m(tmp->str, 1, 1, 1);
	if (!ft_strcmp(tmp->str, ">>") || !ft_strcmp(tmp->str, "<<")
		|| !ft_strcmp(tmp->str, ">") || !ft_strcmp(tmp->str, "<")
		|| !ft_strcmp(tmp->str, "|"))
		return (1);
	return (0);
}

void	ft_check_list(void)
{
	t_lst	*tmp;

	tmp = g_o.args;
	while (tmp)
	{
		if (ft_check_redirects(tmp))
		{
			tmp = tmp->next;
			continue ;
		}
		if (ft_start_preparse(tmp))
			return ;
		tmp = tmp->next;
	}
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
