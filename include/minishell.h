/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 16:49:33 by kferterb          #+#    #+#             */
/*   Updated: 2022/04/24 15:32:06 by kferterb         ###   ########.fr       */
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

typedef struct s_history
{
	char				*data;
	struct s_history	*next;
}	t_log;

typedef struct s_lst
{
	int				fd_in;
	int				fd_out;
	char			**execve;
	char			*str;
	int				pipe_flag;
	int				flag_meta;
	struct s_lst	*next;
}	t_lst;

typedef struct s_o
{
	char	*history_log;
	char	*input;
	char	**split;
	char	**final_args;
	int		ex_code;
	int		count;
	int		count_final;
	int		fd_in;
	int		fd_out;
	int		pipe[2];
	t_lst	*args;
	t_lst	*env;
	t_lst	*final;
	t_log	*first;
	t_log	*page;
}	t_o;

t_o	g_o;

//libft
t_lst	*ft_put_lst_new(void);
t_lst	*ft_lstnew(void *content);
int		ft_lstsize(t_lst *lst);
int		ft_interceptor(t_lst *tmp);
int		ft_strcmp(char *s1, char *s2);
char	**ft_split_mod(char *s, char c);
char	*ft_sjoin(char *s1, char *s2, int flag, int flag2);
void	ft_lstadd_back(t_lst **lst, t_lst *new);
//logic
int		ft_start_preparse(t_lst *tmp);
int		ft_open_file(t_lst *o, int flag);
int		ft_check_quotes(char *s, int *index, char c);
char	**ft_conv_env(void);
char	*ft_find_env(char *s);
char	*find_dollar(char *str);
char	*ft_find_path(char **env, t_lst *tmp);
char	*ft_parse_dollar(char *str, int *index);
char	*ft_parse_quotes(t_lst *o, int *j, char c);
char	*ft_parse_lite(t_lst *o, int flag, int flag2);
char	*ft_substr_m(char *s, int start, int len, int flag);
char	*ft_parse_redirect(t_lst *o, int flag, int flag2);
void	ft_signals(void);
void	ft_free_all(void);
void	ft_check_list(void);
void	ft_preparsing(void);
void	ft_heredoc(t_lst *o);
void	ft_put_list(int flag);
void	ft_put_final_args(void);
void	ft_init_struct(int flag);
void	ft_check_parse(t_lst *o);
void	ft_concatenator(t_lst *tmp, t_lst *tmp2);
void	ft_put_redirect_to_list(t_lst *tmp, int *i);
void	ft_exe(t_lst *tmp, int *pid, char **env, int pipe_fd[2][2]);
//history
t_log	*ft_history_last(t_log *lst);
t_log	*ft_create_history(char *str);
int		ft_get_next_line(int fd);
char	*ft_join(char const *s1, char const *s2, int flag);
void	ft_find_history(void);
void	ft_check_history(void);
void	ft_write_history(t_log *first);
void	ft_history_add_back(t_log **lst, t_log *new);
#endif
