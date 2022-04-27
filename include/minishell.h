/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 16:49:33 by kferterb          #+#    #+#             */
/*   Updated: 2022/04/27 10:00:36 by kferterb         ###   ########.fr       */
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

# define BEGIN(x,y) "\001\033["#x";"#y"m\002"
# define CLOSE "\001\033[0m\002"

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

typedef struct s_history
{
	char				*data;
	struct s_history	*next;
}	t_log;

typedef struct s_o
{
	char	**env;
	char	*input;
	char	**split;
	char	*history_log;
	char	**final_args;
	int		fd_in;
	int		count;
	int		fd_out;
	int		pipe[2];
	int		ex_code;
	int		count_env;
	int		count_final;
	int		buildin_flag;
	int		build_pipe[2];
	t_lst	*args;
	t_log	*page;
	t_lst	*final;
	t_log	*first;
}	t_o;

t_o	g_o;

//libft
t_lst	*ft_put_lst_new(void);
t_lst	*ft_lstnew(void *content);
int		ft_lstsize(t_lst *lst);
int		ft_strcmp(char *s1, char *s2);
char	**ft_split_mod(char *s, char c);
char	*ft_join(char const *s1, char const *s2, int flag);
char	*ft_sjoin(char *s1, char *s2, int flag, int flag2);
void	ft_lstadd_back(t_lst **lst, t_lst *new);
//logic
int		ft_open_file(t_lst *o, int flag);
int		ft_interceptor(t_lst *tmp, int *pipe_fd);
int		ft_check_quotes(char *s, int *index, char c);
char	*ft_redirects(t_lst *o, int *j);
char	*ft_parse_dollar(char *str, int *index);
char	*ft_parse_quotes(t_lst *o, int *j, char c);
char	*ft_parse_redirect(t_lst *o, int flag, int flag2);
char	*ft_substr_m(char *s, int start, int len, int flag);
void	ft_parsing(void);
void	ft_signals(void);
void	ft_free_all(void);
void	ft_multiexe(void);
void	ft_preparsing(void);
void	ft_heredoc(t_lst *o);
void	ft_put_list(int flag);
void	ft_put_final_args(void);
void	ft_init_struct(int flag);
void	ft_proc_signal_handler(int signum);
void	ft_put_redirect_to_list(t_lst *tmp, int *i);
//buildin
int		ft_exit(t_lst *tmp);
int		ft_check_oldpwd(void);
int		ft_export_error_check(char *arg);
void	ft_cd(t_lst *tmp);
void	ft_unset(t_lst *tmp);
void	ft_free_mass(char **str);
void	ft_export_add(char *arg);
void	ft_export_new_env(char *arg);
void	ft_pwd(t_lst *tmp, int *pipe);
void	ft_env(t_lst *tmp, int *pipe);
void	ft_echo(t_lst *tmp, int *pipe);
void	ft_export_add_check(char *arg);
void	ft_export(t_lst *tmp, int *pipe);
void	ft_export_add_env(char *arg, int len);
void	ft_replace_env(char *arg, char *buf, int i);
void	ft_dup(t_lst *tmp, int i, int pipe_fd[2][2]);
void	ft_dup2(t_lst *tmp, int i, int pipe_fd[2][2]);
void	ft_check_out_builtin(t_lst *tmp, int *fd, int *pipe);
//history
t_log	*ft_create_history(char *str);
int		ft_get_next_line(int fd);
void	free_history(void);
void	ft_find_history(void);
void	ft_check_history(void);
void	ft_write_history(t_log *first);
void	ft_history_add_back(t_log **lst, t_log *new);
#endif
