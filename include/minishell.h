/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 16:49:33 by kferterb          #+#    #+#             */
/*   Updated: 2022/04/13 10:39:06 by kferterb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>
# include "../libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>

typedef struct s_lst
{
	char			*str;
	int				flag_meta_symbol;
	struct s_lst	*next;
}	t_lst;

typedef struct s_o
{
	char	*input;
	char	**split;
	int		exit_code;
	int		count_args;
	int		fd_in;
	int		in_file_flag;
	int		fd_out;
	int		out_file_flag;
	int		fd_re_out;
	int		re_out_file_flag;
	int		pipe[2];
	int		heredoc_flag;
	t_lst	*args;
	t_lst	*env;
}	t_o;

t_o	g_o;

t_lst	*ft_lstnew(void *content);

int		ft_strcmp(char *s1, char *s2);
int		ft_check_quotes(char *s, int *index, char c);

char	*ft_gnl(void);
char	*ft_find_env(char *s);
char	*find_dollar(char *str);
char	*ft_redirects(t_lst *o, int *j);
char	**ft_split_mod(char *s, char c);
char	*ft_parse_heredoc(t_lst *o, int *j);
char	*ft_parse_dollar(char *str, int *index);
char	*ft_parse_heredoc_lite(t_lst *o, int *j);
char	*ft_parse_quotes(t_lst *o, int *j, char c);
char	*ft_parse_redirect(t_lst *o, int *j, int flag);
char	*ft_sjoin(char *s1, char *s2, int flag, int flag2);
char	*ft_parse_redirect_lite(t_lst *o, int *j, int flag);
char	*ft_substr_mod(char *s, int start, int len, int flag);

void	ft_parsing(void);
void	ft_signals(void);
void	ft_free_all(void);
void	ft_preparsing(void);
void	ft_init_struct(void);
void	ft_heredoc(char *limit);
void	ft_check_parse(t_lst *o);
void	ft_lstadd_back(t_lst **lst, t_lst *new);

#endif
