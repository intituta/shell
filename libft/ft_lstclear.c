/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 12:25:13 by kferterb          #+#    #+#             */
/*   Updated: 2022/03/04 12:47:54 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list		*list;
	t_list		*new;

	if (!lst || !*lst)
		return ;
	list = *lst;
	while (list != NULL)
	{
		new = list;
		list = list->next;
		del(new->content);
		free(new);
	}
	*lst = NULL;
}
