/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 09:38:14 by kferterb          #+#    #+#             */
/*   Updated: 2022/04/27 09:40:31 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
