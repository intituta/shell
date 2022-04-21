/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_mod.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 18:05:09 by kferterb          #+#    #+#             */
/*   Updated: 2022/04/21 15:36:05 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_count_word_mod(char *s, char c)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (s[++i])
	{
		if (s[i] == '\'')
			if (!ft_check_quotes(s, &i, '\''))
				return (-1);
		if (s[i] == '"')
			if (!ft_check_quotes(s, &i, '"'))
				return (-1);
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
	}
	return (count);
}

void	*ft_mem_free_mod(char **str, int count)
{
	int	i;

	i = -1;
	while (++i < count)
		free(str[i]);
	free(str);
	return (NULL);
}

int	ft_len_word_mod(char *s, char c)
{
	int	len;
	int	flag;

	len = -1;
	flag = 0;
	while (s[++len])
	{
		if (s[len] == '\'' || s[len] == '"')
			flag = 1;
		if (s[len] == '\'')
			ft_check_quotes(s, &len, '\'');
		if (s[len] == '"')
			ft_check_quotes(s, &len, '"');
		if (s[len] == c)
			break ;
	}
	if (flag)
		return (len);
	len = 0;
	while (s[len] != c && s[len])
		len++;
	return (len);
}

char	**ft_fill_word_mod(char *s, char c, int count, char **str)
{
	int	i;
	int	j;
	int	len;

	i = -1;
	while (++i < count)
	{
		while (*s == c)
			s++;
		len = ft_len_word_mod(s, c);
		str[i] = malloc(sizeof(char) * (len + 1));
		if (!str[i])
			return (ft_mem_free_mod(str, count));
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

char	**ft_split_mod(char *s, char c)
{
	char	**str;
	int		count;

	if (!s)
		return (NULL);
	count = ft_count_word_mod(s, c);
	if (count == -1)
	{
		g_o.ex_code = 258;
		return (NULL);
	}
	g_o.count = count;
	str = (char **)malloc(sizeof(char *) * (count + 1));
	if (!str)
		return (NULL);
	str = ft_fill_word_mod(s, c, count, str);
	return (str);
}
