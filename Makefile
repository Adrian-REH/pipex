# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adherrer <adherrer@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/20 12:20:24 by adherrer          #+#    #+#              #
#    Updated: 2024/07/27 21:48:24 by adherrer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = gcc

CFLAGS = -g3 -Werror -Wall -Wextra

RM = rm -rf

SRCS = 	src/pipex.c\
		src/utils_pipex.c\
		lib/libft/libft.a\

SRCS_BONUS = 	bonus/pipex_bonus.c\
				bonus/file_utils.c\
				bonus/utils_pipex_bonus.c\
				lib/libft/libft.a\

BONUS = .bonus
DEFAULT_PART = .default

CYAN = \033[0;96m
DEF_COLOR = \033[0;49m

$(DEFAULT_PART) :
	@echo "$(CYAN) ☕ EXECUTE DEFAULT PART! ☕ $(DEF_COLOR)"
	make all -C lib/libft
	gcc $(CFLAGS) $(SRCS) -o $(NAME)
	@touch $(DEFAULT_PART)
	@echo "$(CYAN) ✨ ¡SUCCESS! ✨ $(DEF_COLOR)"

$(BONUS) :
	@echo "$(CYAN) 🦾 EXECUTE BONUS! 🦾 $(DEF_COLOR)"
	make all -C lib/libft
	gcc $(CFLAGS) $(SRCS_BONUS) -o $(NAME)
	@touch $(BONUS)
	@echo "$(CYAN) ✨ ¡SUCCESS! ✨ $(DEF_COLOR)"

all : $(DEFAULT_PART)

fclean : clean
	$(RM) $(NAME)
	$(RM) $(BONUS)
	$(RM) $(DEFAULT_PART)
	make fclean -C lib/libft
	@echo "$(CYAN) ✨ ¡CLEANED! ✨ $(DEF_COLOR)"

clean :
	@echo "$(CYAN) 🍩 ¡INIT CLEAN! 🍩 $(DEF_COLOR)"
	$(RM) $(NAME)
	make clean -C lib/libft

re : fclean all

bonus : $(BONUS)

.PHONY:     all clean fclean re bonus