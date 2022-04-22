# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/06 10:56:01 by kferterb          #+#    #+#              #
#    Updated: 2022/04/22 13:51:52 by kferterb         ###   ########.fr        #
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
SRC			=	$(addprefix $(SRC_DIR), ft_multipipe.c ft_parsing_utils.c ft_parsing_utils2.c ft_parsing_utils3.c ft_parsing.c ft_signals.c main.c ft_interceptor.c ft_history.c ft_history_utils.c ft_parsing_utils4.c)\
				$(addprefix $(MOD_DIR), ft_gnl_mod.c ft_list_utils.c ft_split_mod.c ft_strcmp_mod.c ft_strjoin_mod.c ft_substr_mod.c)
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
