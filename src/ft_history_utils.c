/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltapioca <ltapioca@21-school.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 09:50:13 by kferterb          #+#    #+#             */
/*   Updated: 2022/04/25 19:43:03 by ltapioca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_log	*ft_history_last(t_log *lst)
{
	if (lst == 0)
		return (NULL);
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

void	ft_history_add_back(t_log **lst, t_log *new)
{
	t_log	*last;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = ft_history_last(*lst);
	last->next = new;
}

int	ft_get_next_line(int fd)
{
	char	buf[10000];
	int		i;

	i = 0;
	while (read(fd, &buf[i], 1) > 0)
	{
		if (buf[i] == '\n')
			break ;
		i++;
	}
	buf[i] = '\0';
	if (buf[0] == '\0')
		return (1);
	add_history(buf);
	return (0);
}

char	*ft_check_flag(int flag, int i, int k)
{
	char	*str;

	if (flag)
		str = malloc(sizeof(*str) * (i + k + 2));
	else
		str = malloc(sizeof(*str) * (i + k + 1));
	return (str);
}

char	*ft_join(char const *s1, char const *s2, int flag)
{
	size_t	i;
	size_t	k;
	size_t	n;
	char	*str;

	if (s1 == 0 || s2 == 0)
		return (NULL);
	i = ft_strlen(s1);
	k = ft_strlen(s2);
	n = 0;
	str = ft_check_flag(flag, i, k);
	if (str == 0)
		return (NULL);
	while (*s1)
		str[n++] = *s1++;
	if (flag == 1)
		str[n++] = ' ';
	if (flag == 2)
		str[n++] = '=';
	while (*s2)
		str[n++] = *s2++;
	str[n] = '\0';
	return (str);
}
