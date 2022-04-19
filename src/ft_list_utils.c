/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 10:50:12 by kferterb          #+#    #+#             */
/*   Updated: 2022/04/19 13:07:35 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_all(void)
{
	int		i;
	t_lst	*tmp;

	i = -1;
	tmp = g_o.args;
	while (g_o.split && g_o.split[++i])
		free(g_o.split[i]);
	free(g_o.split);
	while (tmp)
	{
		free(tmp->str);
		free(tmp);
		tmp = tmp->next;
	}
	tmp = g_o.final;
	while (tmp)
	{
		i = -1;
		while (tmp->execve[++i])
			free(tmp->execve[i]);
		free(tmp->execve);
		free(tmp);
		tmp = tmp->next;
	}
	ft_init_struct(0);
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
