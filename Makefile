# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/20 12:20:24 by adherrer          #+#    #+#              #
#    Updated: 2024/08/02 17:55:25 by adherrer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

NAME_B = pipex_bonus

CC = gcc

CFLAGS = -Werror -Wall -Wextra

RM = rm -rf

LIBFT = lib/libft/libft.a

SRCS = 	src/pipex.c\
		src/utils_pipex.c\
		

SRCS_BONUS = 	bonus/pipex_bonus.c\
				bonus/file_utils.c\
				bonus/catch.c\
				bonus/utils_pipex_bonus.c\

OBJ =  $(SRCS:.c=.o)


OBJ_B =  $(SRCS_BONUS:.c=.o)

CYAN = \033[0;96m
DEF_COLOR = \033[0;49m

$(NAME) : $(OBJ)
	@echo "$(CYAN) ☕ EXECUTE DEFAULT PART! ☕ $(DEF_COLOR)"
	make all -C lib/libft
	gcc $(CFLAGS)  $(OBJ) $(LIBFT) -o $(NAME)
	@echo "$(CYAN) ✨ ¡SUCCESS! ✨ $(DEF_COLOR)"

$(NAME_B) : $(OBJ_B)
	@echo "$(CYAN) 🦾 EXECUTE BONUS! 🦾 $(DEF_COLOR)"
	make all -C lib/libft
	gcc $(CFLAGS) $(OBJ_B) $(LIBFT) -o $(NAME_B)
	@echo "$(CYAN) ✨ ¡SUCCESS! ✨ $(DEF_COLOR)"

all : $(NAME)

fclean : clean
	$(RM) $(NAME)
	$(RM) $(NAME_B)
	make fclean -C lib/libft
	@echo "$(CYAN) ✨ ¡CLEANED! ✨ $(DEF_COLOR)"

clean :
	@echo "$(CYAN) 🍩 ¡INIT CLEAN! 🍩 $(DEF_COLOR)"
	$(RM) $(NAME)
	$(RM) $(OBJ_B)
	$(RM) $(OBJ)
	make clean -C lib/libft

re : fclean all

bonus : $(NAME_B)

.PHONY:     all clean fclean re bonus
