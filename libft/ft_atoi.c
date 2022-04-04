/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 18:30:59 by kferterb          #+#    #+#             */
/*   Updated: 2022/04/03 18:39:27 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_atoi(char *str)
{
	int			i;
	long int	j;
	int			k;

	i = 0;
	j = 0;
	k = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			k = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		j = j * 10 + k * (str[i] - '0');
		i++;
	}
	return (j);
}
