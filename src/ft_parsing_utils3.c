/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_utils3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 13:19:02 by kferterb          #+#    #+#             */
/*   Updated: 2022/04/19 14:30:23 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_put_quotes_to_list(t_lst *tmp, int *i, char c)
{
	char	*start;
	t_lst	*tmp2;

	start = ft_substr(tmp->str, 0, *i);
	if (ft_strlen(start) > 0)
	{
		if (tmp->str[*i + 1] == '\0' || tmp->str[*i + 1] == '"'
			|| tmp->str[*i + 1] == '\'' || tmp->str[*i - 1] == '\0'
			|| tmp->str[*i - 1] == '"' || tmp->str[*i - 1] == '\'')
			return ;
		tmp2 = ft_lstnew(ft_substr_m(tmp->str, *i + 1, ft_strlen(tmp->str), 1));
		tmp->str = ft_substr_m(start, 0, ft_strlen(start), 1);
	}
	else
	{
		if (!ft_check_quotes(tmp->str, i, c))
			return ;
		if (tmp->str[*i + 1] == '\0'
			|| tmp->str[*i + 1] == '"' || tmp->str[*i + 1] == '\'')
			return ;
		free(start);
		tmp2 = ft_lstnew(ft_substr(tmp->str, *i + 1, ft_strlen(tmp->str)));
		tmp->str = ft_substr_m(tmp->str, 0, *i + 1, 1);
	}
	ft_concatenator(tmp, tmp2);
}

void	ft_put_redirect_to_list(t_lst *tmp, int *i)
{
	char	*start;
	t_lst	*tmp2;

	start = ft_substr(tmp->str, 0, *i);
	if (ft_strlen(start) > 0)
	{
		tmp2 = ft_lstnew(ft_substr_m(tmp->str, *i, ft_strlen(tmp->str), 1));
		tmp->str = ft_substr_m(start, 0, ft_strlen(start), 1);
	}
	else
	{
		free(start);
		if ((tmp->str[*i] != '|' && tmp->str[*i + 1] == '>')
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
	}
	ft_concatenator(tmp, tmp2);
}

void	ft_put_final_args(void)
{
	if (!g_o.final)
		g_o.final = ft_put_lst_new();
	else
		ft_lstadd_back(&g_o.final, ft_put_lst_new());
}

void	ft_check_put_list(int flag)
{
	g_o.count_final = 0;
	if (flag)
	{
		while (g_o.args)
		{
			if (ft_strlen(g_o.args->str))
				g_o.final_args[g_o.count_final++] = ft_strdup(g_o.args->str);
			free(g_o.args->str);
			free(g_o.args);
			g_o.args = g_o.args->next;
		}
	}
	else
	{
		while (g_o.args && !g_o.args->pipe_flag)
		{
			if (ft_strlen(g_o.args->str))
				g_o.final_args[g_o.count_final++] = ft_strdup(g_o.args->str);
			free(g_o.args->str);
			free(g_o.args);
			g_o.args = g_o.args->next;
		}
	}
}

void	ft_put_list(int flag)
{
	t_lst	*tmp;

	g_o.count_final = 0;
	tmp = g_o.args;
	if (flag)
	{
		while (tmp)
		{
			if (ft_strlen(tmp->str) != 0)
				g_o.count_final++;
			tmp = tmp->next;
		}
	}
	else
	{
		while (tmp && tmp->pipe_flag != 1)
		{
			if (ft_strlen(tmp->str) != 0)
				g_o.count_final++;
			tmp = tmp->next;
		}
	}
	g_o.final_args = malloc(sizeof(char *) * g_o.count_final + 1);
	ft_check_put_list(flag);
	g_o.final_args[g_o.count_final] = NULL;
}
