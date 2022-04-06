# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kferterb <kferterb@student.21-school.ru    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/06 10:56:01 by kferterb          #+#    #+#              #
#    Updated: 2022/04/06 20:04:07 by kferterb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY : all clean fclean re check_obj_dir

COL_0					:=	\033[38;2;0;145;15
COL_1					:=	\033[38;2;46;84;240
COL_2					:=	\033[37
UNSET					:=	\033[m

NAME					:=	minishell

CC						:=	clang
OBJ_DIR					:=	obj
FLAGS					:=	-Wall -Wextra -Werror
INCLUDE					:=	include

LIBFT_DIR				:=	libft
LIBS					:=	$(LIBFT_DIR)/libft.a \
							-L /Users/$(USER)/.brew/opt/readline/lib -lreadline

VPATH					:=	src \

SRC						:=	main.c \
							ft_signals.c \
							ft_parse_utils.c


OBJ						:=	$(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))
DEP						:=	$(wildcard $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.d))))

all						:	other_libs_rule $(OBJ_DIR) $(NAME)

$(NAME)					:	$(OBJ)
							@$(CC) $(OBJ) $(LIBS) -o $@
							@echo "$(COL_0);1m"
							@echo "\t\tCOMMAND + V"
							@echo "$(UNSET)"
							@printf "$(shell pwd)/$@" | pbcopy

$(OBJ_DIR)/%.o			:	%.c
							$(CC) $(FLAGS) -I $(INCLUDE) -MD -c $< -o $@

$(OBJ_DIR)				:
							@mkdir -p $(OBJ_DIR)/

other_libs_rule:	$(LIBFT_DIR)
							@make -C $<

include $(DEP)

clean					:
							@make clean -C $(LIBFT_DIR)
							@rm -rf $(OBJ_DIR)
							@echo "$(COL_1);3;1mobject\033[23;22m files for \033[3;1m$(NAME)\033[23;22m have been deleted\033[0m"

fclean					:	clean
							@rm -f $(NAME)
							@echo "$(COL_1);3;1m$(NAME)\033[23;22m have been deleted\033[0m"

re						:	fclean all
