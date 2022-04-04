/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 18:04:21 by kferterb          #+#    #+#             */
/*   Updated: 2022/04/03 18:24:40 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2, int f1, int f2)
{
	int		i;
	int		j;
	char	*res;

	if (!s1 || !s2)
		return (0);
	res = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	i = -1;
	while (s1[++i])
		res[i] = s1[i];
	j = -1;
	while (s2[++j])
		res[i + j] = s2[j];
	res[i + j] = '\0';
	if (f1)
		free(s1);
	if (f2)
		free(s2);
	return (res);
}
