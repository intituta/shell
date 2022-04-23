/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 10:50:12 by kferterb          #+#    #+#             */
/*   Updated: 2022/04/23 09:32:11 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_lstsize(t_lst *lst)
{
	int		len;

	if (!lst)
		return (0);
	len = 0;
	while (lst)
	{
		len++;
		lst = lst -> next;
	}
	return (len);
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
	head -> flag_meta = 0;
	head -> pipe_flag = 0;
	head -> fd_in = -2;
	head -> fd_out = -2;
	head -> execve = NULL;
	return (head);
}

t_lst	*ft_put_lst_new(void)
{
	int		i;
	t_lst	*head;

	i = -1;
	head = (t_lst *)malloc(sizeof(t_lst));
	if (!head)
		return (NULL);
	head -> next = NULL;
	head -> str = NULL;
	head -> flag_meta = 0;
	head -> pipe_flag = 0;
	head -> fd_in = g_o.fd_in;
	head -> fd_out = g_o.fd_out;
	g_o.fd_in = -2;
	g_o.fd_out = -2;
	head -> execve = malloc(sizeof(char *) * g_o.count_final + 1);
	while (g_o.final_args[++i])
		head->execve[i] = ft_strdup(g_o.final_args[i]);
	head->execve[i] = NULL;
	i = -1;
	while (g_o.final_args[++i])
		free(g_o.final_args[i]);
	free(g_o.final_args);
	return (head);
}
