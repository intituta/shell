/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 16:49:33 by kferterb          #+#    #+#             */
/*   Updated: 2022/04/10 10:37:22 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>
# include "../libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>

typedef struct s_args
{
	char	*str;
}	t_args;

typedef struct s_s
{
	char	*in;
	char	**env;
	char	**str;
	char	*heredoc;
	int		ex_code;
	int		count_args;
	t_args	*t_a;
}	t_s;

void	ft_sig(void);
void	ft_parsing(void);
void	ft_redirects(void);
void	ft_heredoc(char *limit);

char	*ft_gnl(void);
char	*ft_find_env(char *s);
char	*find_dollar(char *str);
char	**ft_split_mod(char *s, char c);
char	*ft_parse_dollar(char *str, int *index);

int		ft_strcmp(char *s1, char *s2);
int		ft_check_quotes(char *s, int *index, char c);
int		ft_check_quotes(char *s, int *index, char c);

t_s	*g_s;

#endif
