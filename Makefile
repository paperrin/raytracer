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

CFLAGS		=	-Wall -Wextra -Werror -std=c89 -pedantic \
				-Wmissing-prototypes -Wstrict-prototypes \
				-Wold-style-definition -Wno-long-long

#CFLAGS		+=	-g -O3 -fsanitize=address

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
				opencl/opencl_get_info.c						\
				opencl/opencl_create.c							\
				opencl/opencl_kernel_destroy.c					\
				opencl/opencl_kernel_load_from_file.c			\
				opencl/opencl_kernel_load_from_file_utils.c		\
				opencl/opencl_kernel_create_n_args.c			\
				opencl/opencl_print_info.c						\
				opencl/opencl_destroy.c							\
				opencl/opencl_kernel_arg.c						\
				opencl/opencl_platform_utils.c					\
				opencl/opencl_device_utils.c					\
				\
				kernel/kernel_ray_gen_primary.c					\
				kernel/kernel_ray_trace.c						\
				kernel/kernel_clear.c							\
				kernel/kernel_ray_shade.c						\
				kernel/kernel_ray_shade_args.c					\
				kernel/kernel_post_process.c					\
				\
				callbacks/callback_key.c						\
				\
				camera/camera_rotation.c						\
				camera/matrix_real16.c							\
				camera/matrix_real16_rot.c						\
				\
				vec/vec3r.c										\
				vec/vec3f.c										\
				vec/vec2r.c										\
				\
				scene_parser/cstream/cstream.c							\
				scene_parser/cstream/cstream_skip_chars.c				\
				\
				scene_parser/tkstream/tkstream.c					\
				scene_parser/tkstream/tkstream_error.c				\
				scene_parser/tkstream/tkstream_read_token.c			\
				scene_parser/tkstream/tkstream_read_punc.c			\
				scene_parser/tkstream/tkstream_read_str.c			\
				scene_parser/tkstream/tkstream_read_num.c			\
				scene_parser/tkstream/tkstream_read_op.c			\
				scene_parser/tkstream/tkstream_read_var.c			\
				\
				scene_parser/token/token_destroy.c							\
				scene_parser/token/token_print.c							\
				scene_parser/token/token_eval.c								\
				scene_parser/token/token_punc.c								\
				scene_parser/token/token_op.c								\
				scene_parser/token/token_var.c								\
				scene_parser/token/token_str.c								\
				scene_parser/token/token_call.c								\
				scene_parser/token/token_num.c								\
				scene_parser/token/token_bool.c								\
				scene_parser/token/token_class.c							\
				scene_parser/token/token_op_eval.c							\
				scene_parser/token/token_call_eval.c						\
				scene_parser/token/token_var_eval.c							\
				\
				scene_parser/ast/ast_parse.c						\
				scene_parser/ast/ast_parse_expr.c					\
				scene_parser/ast/ast_parse_maybe_call.c				\
				\
				scene_parser/interpreter/interpreter.c					\
				scene_parser/interpreter/interpreter_class.c			\
				scene_parser/interpreter/interpreter_method.c			\
				scene_parser/interpreter/interpreter_var.c				\
				scene_parser/interpreter/interpreter_find_method.c		\
				\
				scene_parser/hooks/interpreter_add_all_hooks.c									\
				scene_parser/hooks/interpreter_add_class_console.c								\
				scene_parser/hooks/interpreter_method_stub_args_set_color.c						\
				scene_parser/hooks/interpreter_method_stub_args_set_pos.c						\
				scene_parser/hooks/interpreter_method_stub_args_set_rot.c						\
				scene_parser/hooks/global/interpreter_method_transform.c						\
				scene_parser/hooks/global/internal_global_method_set.c							\
				scene_parser/hooks/obj/internal_obj_methods.c									\
				scene_parser/hooks/obj/interpreter_add_class_obj_sphere.c						\
				scene_parser/hooks/obj/interpreter_add_class_obj_aligned_cube.c					\
				scene_parser/hooks/obj/interpreter_add_class_obj_cylinder.c						\
				scene_parser/hooks/obj/interpreter_add_class_obj_plane.c						\
				scene_parser/hooks/obj/interpreter_add_class_obj_cone.c							\
				scene_parser/hooks/material/interpreter_add_class_material.c					\
				scene_parser/hooks/material/internal_material_method_color.c					\
				scene_parser/hooks/material/internal_material_method_reflection.c				\
				scene_parser/hooks/material/internal_material_method_refraction.c				\
				scene_parser/hooks/material/internal_material_method_specular.c					\
				scene_parser/hooks/material/internal_material_method_emission.c					\
				scene_parser/hooks/material/internal_material_method_ignores_light.c			\
				scene_parser/hooks/material/internal_material_method_projection.c				\
				scene_parser/hooks/material/internal_material_method_color_map.c				\
				scene_parser/hooks/texture/interpreter_add_class_texture.c						\
				scene_parser/hooks/texture/internal_texture_method_translate.c					\
				scene_parser/hooks/texture/internal_texture_method_scale.c						\
				scene_parser/hooks/texture/internal_texture_method_filter.c						\
				scene_parser/hooks/texture/interpreter_add_class_texture_checkerboard.c			\
				scene_parser/hooks/texture/internal_texture_method_colors.c						\
				scene_parser/hooks/texture/internal_texture_method_wave_colors.c				\
				scene_parser/hooks/texture/interpreter_add_class_texture_sine.c					\
				scene_parser/hooks/texture/interpreter_add_class_texture_noise.c				\
				scene_parser/hooks/texture/internal_texture_method_factors.c					\
				scene_parser/hooks/light/interpreter_add_class_point_light.c					\
				scene_parser/hooks/light/interpreter_add_class_distant_light.c					\
				scene_parser/hooks/light/interpreter_add_class_spot_light.c						\
				scene_parser/hooks/light/internal_spot_light_methods.c							\
				scene_parser/hooks/light/internal_light_method_color.c							\
				scene_parser/hooks/light/internal_light_method_intensity.c						\
				scene_parser/hooks/light/internal_light_method_glare.c							\
				scene_parser/hooks/light/internal_light_method_dispersion.c						\
				scene_parser/hooks/config/interpreter_add_class_config.c						\
				scene_parser/hooks/config/internal_config_method_ambient.c						\
				scene_parser/hooks/config/internal_config_method_camera_light.c					\
				scene_parser/hooks/config/internal_config_method_recursion_depth.c				\
				scene_parser/hooks/config/internal_config_method_projection_depth.c				\
				scene_parser/hooks/config/internal_config_method_post_filter.c					\
				scene_parser/hooks/config/internal_config_method_screen_size.c					\
				scene_parser/hooks/config/internal_config_method_sample_level.c					\
				scene_parser/hooks/config/internal_config_method_zfar.c							\
				scene_parser/hooks/camera/interpreter_add_class_camera.c						\
				scene_parser/hooks/camera/internal_camera_method_speed.c						\
				scene_parser/hooks/camera/internal_camera_method_anaglyph.c						\
				scene_parser/hooks/hook_valid_args.c											\
				\
				prompt/arg_dispatch.c							\
				prompt/arg_devices.c							\
				\
				scene/scene.c											\
				scene/scene_map.c										\
				scene/scene_map_search.c								\
				scene/scene_transform.c									\
				scene/scene_transform_stack.c							\
				scene/scene_sphere.c									\
				scene/scene_plane.c										\
				scene/scene_cylinder.c									\
				scene/scene_cone.c										\
				scene/scene_aligned_cube.c								\
				scene/scene_point_light.c								\
				scene/scene_dir_light.c									\
				scene/scene_spot_light.c								\
				scene/scene_material.c									\
				scene/scene_texture.c									\
				scene/scene_texture_wave.c								\
				scene/scene_texture_checkerboard.c						\
				scene/scene_texture_noise.c								\
				scene/scene_camera.c									\
				\
				main.c											\
				render.c										\
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
