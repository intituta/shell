# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/03 16:50:27 by kferterb          #+#    #+#              #
#    Updated: 2022/04/04 09:59:30 by kferterb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell

SRCS			=	main.c \
					./libft/ft_substr.c \
					./libft/ft_strjoin.c \
					./libft/ft_strncmp.c \
					./libft/ft_atoi.c \
					./libft/ft_itoa.c  \
					ft_signals.c

HEADER			=	minishell.h

OBJS			=	$(SRCS:%.c=%.o)

CC				=	gcc

CFLAGS			=	-Wall -Wextra -Werror

READLINE		=	-L /Users/$(USER)/.brew/opt/readline/lib -lreadline

.PHONY			:	all clean fclean re

all				:	$(NAME) clean

$(NAME)			:	$(OBJS) $(HEADER)
					$(CC) $(CFLAGS) $(READLINE) $(OBJS) -o $(NAME)

%.o 			:	%.c $(HEADER)
					$(CC) $(CFLAGS) -c $< -o $@

clean			:
					@rm -f $(OBJS)

fclean			:	clean
					@$(RM) $(NAME)

re				:	fclean all
