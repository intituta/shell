/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 16:49:33 by kferterb          #+#    #+#             */
/*   Updated: 2022/04/04 10:13:40 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <readline/history.h>
# include <readline/readline.h>

typedef struct s_s
{
	char	*in;
	char	**env;
	int		ex_code;
}	t_s;

t_s	*g_s;

int		ft_strlen(char *s);
int		ft_atoi(char *str);
int		ft_strncmp(char *s1, char *s2, int len);

char	*ft_itoa(int n);
char	*ft_substr(char *s, int start, int len);
char	*ft_strjoin(char *s1, char *s2, int f1, int f2);

void	ft_sig(void);

#endif
