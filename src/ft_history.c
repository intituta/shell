/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 09:48:18 by kferterb          #+#    #+#             */
/*   Updated: 2022/04/27 09:23:07 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_write_history(t_log *first)
{
	int		fd;

	fd = open(g_o.history_log, O_CREAT | O_RDWR | O_APPEND,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
		exit (1);
	free(g_o.history_log);
	first = first->next;
	while (first != NULL)
	{
		write(fd, first->data, ft_strlen(first->data));
		write(fd, "\n", 1);
		first = first->next;
	}
	close(fd);
}

void	ft_find_history(void)
{
	char	*path;

	path = NULL;
	path = getcwd(path, 1000);
	g_o.history_log = ft_join(path, "/.minishell_history", 0);
	free (path);
}

void	ft_check_history(void)
{
	char	*path;
	char	*loc;
	int		fd;

	path = NULL;
	path = getcwd(path, 1000);
	loc = ft_join(path, "/.minishell_history", 0);
	fd = open(loc, O_RDWR);
	if (fd < 3)
		return ;
	while (ft_get_next_line(fd) == 0)
		ft_get_next_line(fd);
	free(loc);
	free(path);
}

t_log	*ft_create_history(char *str)
{
	t_log	*page;

	page = malloc(sizeof(page));
	page->data = str;
	page->next = NULL;
	return (page);
}
