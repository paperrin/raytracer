# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: paperrin <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/07/29 19:37:35 by paperrin          #+#    #+#              #
#*   Updated: 2017/11/11 03:24:21 by paperrin         ###   ########.fr       *#
#                                                                              #
# **************************************************************************** #

NAME		=	rt

CC			=	gcc

CFLAGS		=	-g -O3 -Wall -Wextra -Werror -std=c89 -pedantic \
				-Wmissing-prototypes -Wstrict-prototypes \
				-Wold-style-definition -Wno-long-long -fsanitize=address

RM			=	rm -rf

SRC_DIR		=	./src/

OBJ_DIR		=	./obj/

INC_DIRS	=	./include/			\
				./glfw/include/		\
				./libft/include/

LIB_DIRS	=	./libft/			\
				./glfw/build/src/

LIBS		=	-lft \
				-lglfw3 -framework Cocoa -framework OpenGL -framework IOKit \
				-framework CoreVideo -framework OpenCL

INC_PARAMS	=	$(INC_DIRS:%=-I%)

LIB_PARAMS	=	$(LIB_DIRS:%=-L%)

CFILES		=	\
				graphics/window.c								\
				graphics/window_render.c						\
				graphics/window_callback.c						\
				graphics/window_callback_key.c					\
				graphics/window_callback_mouse_motion.c			\
				graphics/window_callback_mouse_button.c			\
				graphics/window_callback_mouse_scroll.c			\
				graphics/image.c								\
				\
				callbacks/callback_key.c						\
				\
				main.c


SRC			=	$(CFILES:%=$(SRC_DIR)%)

OBJ			=	$(CFILES:%.c=$(OBJ_DIR)%.o)

OBJ_SUBDIR	=	$(sort $(dir $(OBJ)))

# # # # #

all				:	libs $(OBJ_DIR) $(NAME)

$(NAME)			:	$(OBJ) ./libft/libft.a
						$(CC) $(OBJ) -o $@ $(LIBS) $(LIB_PARAMS) $(CFLAGS)

libs			:	glfw
					make -C ./libft/

glfw			:
						@if [ ! -d "./glfw/build" ]; then \
							mkdir -p ./glfw/build; \
							cd ./glfw/build; cmake ..; \
						fi
						make -C ./glfw/build/src

$(OBJ_DIR)%.o	:	$(SRC_DIR)%.c
						mkdir -p $(OBJ_DIR)
						$(CC) $(CFLAGS) $(INC_PARAMS) -MMD -MP -c $< -o $@

$(OBJ_DIR)		:
					mkdir -p $(OBJ_DIR)
					mkdir -p $(OBJ_SUBDIR)

clean			:
						$(RM) $(OBJ_DIR)
						make -C ./libft/ clean
						@if [ -d "./glfw/build/src" ]; then \
							make -C ./glfw/build/src clean; \
						fi
						$(RM) ./glfw/build

fclean			:	clean
						$(RM) $(NAME)
						make -C ./libft/ fclean

re				:	fclean all

norm			:
	@echo "\x1b[35m\n.==================[ \x1b[0m\c"
	@echo "\x1b[35;1mNormi-Check\x1b[0m\c"
	@echo " \x1b[35m]==================.\x1b[31;1m"
	@norminette include/ src/ \
		| tr "\n" "@" \
		| sed -e "s/Norme: /$$/g" \
		| tr "$$" "\n" \
		| grep -e Error -e Warning \
		| tr "@" "\n" \
		| sed "N;$$!P;$$!D;$$d"
	@echo "\x1b[0m\x1b[35m\c"
	@echo ".___________________________________________________.\n\x1b[0m"

-include $(OBJ:.o=.d)

.PHONY : all, clean, fclean, re, norm, glfw
