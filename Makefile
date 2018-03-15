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
				opencl/opencl_get_device_info.c					\
				opencl/opencl_create.c							\
				opencl/opencl_kernel_destroy.c					\
				opencl/opencl_kernel_load_from_file.c			\
				opencl/opencl_kernel_load_from_file_utils.c		\
				opencl/opencl_kernel_create_n_args.c			\
				opencl/opencl_print_device_info.c				\
				opencl/opencl_destroy.c							\
				opencl/opencl_kernel_arg.c						\
				\
				kernel/kernel_ray_gen_primary.c					\
				kernel/kernel_ray_trace.c						\
				kernel/kernel_clear.c							\
				kernel/kernel_ray_shade.c						\
				\
				callbacks/callback_key.c						\
				callbacks/callback_mouse_motion.c				\
				\
				camera/camera.c									\
				camera/camera_rotation.c						\
				camera/camera_translate.c						\
				camera/matrix_real16.c							\
				camera/matrix_real16_rot.c						\
				\
				vec/vec3r.c										\
				vec/vec3f.c										\
				\
				obj/obj_sphere.c								\
				obj/obj_plane.c									\
				\
				scene_parser/cstream/cstream.c							\
				scene_parser/cstream/cstream_skip_chars.c				\
				scene_parser/tkstream/tkstream.c					\
				scene_parser/tkstream/tkstream_read_token.c			\
				scene_parser/tkstream/tkstream_read_punc.c			\
				scene_parser/tkstream/tkstream_read_str.c			\
				scene_parser/tkstream/tkstream_read_num.c			\
				scene_parser/tkstream/tkstream_read_op.c			\
				scene_parser/tkstream/tkstream_read_var.c			\
				scene_parser/token/token_destroy.c						\
				scene_parser/token/token_punc_destroy.c					\
				scene_parser/token/token_num_destroy.c					\
				scene_parser/token/token_str_destroy.c					\
				scene_parser/token/token_kw_destroy.c					\
				scene_parser/token/token_var_destroy.c					\
				scene_parser/token/token_op_destroy.c					\
				scene_parser/token/token_call_destroy.c					\
				scene_parser/token/token_bool_destroy.c					\
				scene_parser/ast/ast_parse.c						\
				scene_parser/ast/ast_parse_expr.c					\
				scene_parser/ast/ast_parse_maybe_call.c				\
				\
				main.c											\
				process_input.c									\
				error.c


SRC			=	$(CFILES:%=$(SRC_DIR)%)

OBJ			=	$(CFILES:%.c=$(OBJ_DIR)%.o)

OBJ_SUBDIR	=	$(sort $(dir $(OBJ)))

# # # # #

all				:	libs subdirs $(NAME)

$(NAME)			:	$(OBJ) ./libft/libft.a
						$(CC) $(OBJ) -o $@ $(LIBS) $(LIB_PARAMS) $(CFLAGS)

libs			:
						@if [ ! -d "./glfw/build" ]; then \
							mkdir -p ./glfw/build; \
							cd ./glfw/build; \
							cmake ..; \
							cd ../..; \
							make -C ./glfw/build; \
						fi
						make -C ./libft/

$(OBJ_DIR)%.o	:	$(SRC_DIR)%.c
						make subdirs
						$(CC) $(CFLAGS) $(INC_PARAMS) -MMD -MP -c $< -o $@

subdirs			:
						@mkdir -p $(OBJ_DIR)
						@mkdir -p $(OBJ_SUBDIR)

clean			:
						$(RM) $(OBJ_DIR)

fclean			:	clean
						$(RM) $(NAME)
						@if [ -d "./glfw/build/src" ]; then \
							make -C ./glfw/build/src clean; \
						fi
						$(RM) ./glfw/build
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

.PHONY : all, libs, subdirs, clean, fclean, re, norm
