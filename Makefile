# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/06 10:56:01 by kferterb          #+#    #+#              #
#    Updated: 2022/04/27 13:29:55 by kferterb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra
HEADER		=	include/minishell.h
RM			=	rm -f
LIBS		=	-L libft -lft
READLINE	=	-L /Users/$(USER)/.brew/opt/readline/lib -lreadline
SRC_DIR		=	src/
MOD_DIR		=	libft_mod/
BUILDIN		=	buildin/
SRC			=	$(addprefix $(SRC_DIR), main.c ft_signals.c ft_preparsing.c ft_preparsing_utils.c ft_parsing.c ft_parsing_quotes.c ft_parse_redirects.c ft_parse_pipes.c ft_parse_dollar.c ft_history.c ft_history_utils.c ft_free.c ft_exe.c ft_exe_utils.c ft_shlvl.c)\
				$(addprefix $(MOD_DIR), ft_list_utils.c ft_split_mod.c ft_strcmp_mod.c ft_strjoin_mod.c ft_substr_mod.c)\
				$(addprefix $(BUILDIN), ft_env.c ft_pwd.c ft_echo.c ft_export.c ft_export_add.c ft_export_add2.c ft_unset.c ft_exit.c ft_cd.c ft_cd_utils.c)
OBJS		=	$(SRC:%.c=%.o)
.PHONY		:	all clean fclean re
all			:	$(NAME)
$(NAME)		:	$(OBJS)
				@make -C libft
				@$(CC) $(LIBS) $(READLINE) $(CFLAGS) $(OBJS) -o $(NAME)
%.o			:	%.c $(HEADER)
				@$(CC) $(CFLAGS) -c $< -o $@
clean		:
				@make -C libft clean
				$(RM) $(OBJS)
fclean		:	clean
				@make -C libft fclean
				$(RM) $(NAME)
re			:	fclean all
