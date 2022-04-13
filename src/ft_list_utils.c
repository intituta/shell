/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 10:50:12 by kferterb          #+#    #+#             */
/*   Updated: 2022/04/13 09:40:49 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_all(void)
{
	int		i;
	t_lst	*tmp;
	t_lst	*tmp2;

	i = -1;
	tmp = g_o.args;
	tmp2 = g_o.env;
	if (g_o.input)
		free(g_o.input);
	while (g_o.split[++i])
		free(g_o.split[i]);
	free(g_o.split);
	while (tmp)
	{
		free(tmp->str);
		free(tmp);
		tmp = tmp->next;
	}
	while (tmp2)
	{
		free(tmp2->str);
		free(tmp2);
		tmp2 = tmp2->next;
	}
	ft_init_struct();
}

t_lst	*ft_lstlast(t_lst *lst)
{
	if (!lst)
		return (lst);
	while (lst -> next)
		lst = lst -> next;
	return (lst);
}

void	ft_lstadd_back(t_lst **lst, t_lst *new)
{
	if (!new || !lst)
		return ;
	if (*lst)
		ft_lstlast(*lst)->next = new;
	else
		*lst = new;
}

t_lst	*ft_lstnew(void *content)
{
	t_lst	*head;

	head = (t_lst *)malloc(sizeof(t_lst));
	if (!head)
		return (NULL);
	head -> next = NULL;
	head -> str = content;
	head -> flag_meta_symbol = 0;
	return (head);
}
