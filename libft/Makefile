# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/04 12:30:52 by kferterb          #+#    #+#              #
#    Updated: 2022/04/06 10:52:55 by kferterb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libft.a

SRCS		=	ft_bzero.c			ft_isalnum.c		ft_isalpha.c\
				ft_isascii.c		ft_isdigit.c		ft_isprint.c\
				ft_memcpy.c			ft_memmove.c		ft_memset.c\
				ft_strlcat.c		ft_strlcpy.c		ft_strlen.c\
				ft_toupper.c		ft_tolower.c		ft_strchr.c\
				ft_strrchr.c		ft_strncmp.c		ft_memchr.c\
				ft_memcmp.c			ft_strnstr.c		ft_atoi.c\
				ft_calloc.c			ft_strdup.c			ft_substr.c\
				ft_strjoin.c		ft_strtrim.c		ft_striteri.c\
				ft_putnbr_fd.c		ft_putchar_fd.c		ft_putstr_fd.c\
				ft_putendl_fd.c		ft_strmapi.c		ft_itoa.c\
				ft_split.c

SRCS_BONUS	=	ft_lstmap.c			ft_lstnew.c			ft_lstsize.c\
				ft_lstdelone.c		ft_lstiter.c		ft_lstlast.c\
				ft_lstadd_back.c	ft_lstadd_back.c	ft_lstadd_front.c\
				ft_lstclear.c		ft_lstclear.c

HEADER		=	libft.h

OBJ			=	$(SRCS:%.c=%.o)

OBJ_BONUS	=	$(SRCS_BONUS:%.c=%.o)

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror -I$(HEADER)

.PHONY		:	all clean fclean re

all			:	$(NAME)

$(NAME)		:	$(OBJ) $(HEADER)
				ar rcs  $(NAME) $?

%.o 		: 	%.c $(HEADER)
				$(CC) $(CFLAGS) -c $< -o $@

bonus		:
				@make OBJ="$(OBJ_BONUS)" all

clean		:
				@rm -f $(OBJ) $(OBJ_BONUS) $(NAME)

fclean		:	clean
				@$(RM) $(NAME) $(OBJ_BONUS)

re			:	fclean all
