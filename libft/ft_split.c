/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 12:39:06 by kferterb          #+#    #+#             */
/*   Updated: 2022/03/04 12:29:32 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_word(char const *s, char c)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (s[++i])
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
	return (count);
}

void	*ft_mem_free(char **str, int count)
{
	int	i;

	i = -1;
	while (++i < count)
		free(str[i]);
	free(str);
	return (NULL);
}

int	ft_len_word(char const *s, char c)
{
	int	len;

	len = 0;
	while (s[len] != c && s[len] != '\0')
		len++;
	return (len);
}

char	**ft_fill_word(char const *s, char c, int count, char **str)
{
	int	i;
	int	j;
	int	len;

	i = -1;
	while (++i < count)
	{
		while (*s == c)
			s++;
		len = ft_len_word(s, c);
		str[i] = (char *)malloc(sizeof(char) * (len + 1));
		if (!str[i])
			return (ft_mem_free(str, count));
		j = -1;
		while (++j < len)
		{
			str[i][j] = *s;
			s++;
		}
		str[i][j] = '\0';
	}
	str[i] = NULL;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		count;

	if (!s)
		return (NULL);
	count = ft_count_word(s, c);
	str = (char **)malloc(sizeof(char *) * (count + 1));
	if (!str)
		return (NULL);
	str = ft_fill_word(s, c, count, str);
	return (str);
}
