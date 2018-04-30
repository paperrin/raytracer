# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: paperrin <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/03 12:00:36 by paperrin          #+#    #+#              #
#*   Updated: 2017/10/19 17:39:59 by paperrin         ###   ########.fr       *#
#                                                                              #
# **************************************************************************** #

NAME		=	libft.a

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror -std=c89 -pedantic \
				-Wmissing-prototypes -Wstrict-prototypes \
				-Wold-style-definition -Wno-long-long

#CFLAGS		+= -g -O3 -fsanitize=address

RM			=	rm -rf

SRC_DIR		=	./src/

OBJ_DIR		=	./obj/

INC_DIR		=	./include/

CFILES		=	ft_swap.c			\
				ft_string.c			\
				ft_memset.c			\
				ft_bzero.c			\
				ft_memcpy.c			\
				ft_memrevcpy.c		\
				ft_memccpy.c		\
				ft_memmove.c		\
				ft_memchr.c			\
				ft_memchr_any.c		\
				ft_memcmp.c			\
				ft_memrealloc.c		\
				ft_strlen.c			\
				ft_wstrlen.c		\
				ft_strdup.c			\
				ft_strndup.c		\
				ft_wstrdup.c		\
				ft_strcpy.c			\
				ft_wstrcpy.c		\
				ft_strncpy.c		\
				ft_strcat.c			\
				ft_strncat.c		\
				ft_strlcat.c		\
				ft_strchr.c			\
				ft_strchr_any.c		\
				ft_strrchr.c		\
				ft_strstr.c			\
				ft_strnstr.c		\
				ft_strcmp.c			\
				ft_strncmp.c		\
				ft_atoi.c			\
				ft_atoi_base.c		\
				ft_atoi_hex.c		\
				ft_atof.c			\
				ft_is_whitespace.c	\
				ft_isalpha.c		\
				ft_isdigit.c		\
				ft_isalnum.c		\
				ft_isascii.c		\
				ft_isprint.c		\
				ft_toupper.c		\
				ft_tolower.c		\
				ft_strupr.c			\
				ft_strlwr.c			\
				ft_memalloc.c		\
				ft_memdel.c			\
				ft_strnew.c			\
				ft_strdel.c			\
				ft_strclr.c			\
				ft_striter.c		\
				ft_striteri.c		\
				ft_strmap.c			\
				ft_strmapi.c		\
				ft_strequ.c			\
				ft_strnequ.c		\
				ft_strsub.c			\
				ft_strjoin.c		\
				ft_strnjoin.c		\
				ft_wstrjoin.c		\
				ft_wstrjoin_free.c	\
				ft_strtrim.c		\
				ft_strsplit.c		\
				ft_itoa.c			\
				ft_itoa_base.c		\
				ft_itoa_hex.c		\
				ft_itoa_oct.c		\
				ft_itoa_bin.c		\
				ft_itoa_dec.c		\
				ft_ftoa.c			\
				ft_putfloat.c		\
				ft_putchar.c		\
				ft_putwchar.c		\
				ft_putnchar.c		\
				ft_putstr.c			\
				ft_putnstr.c		\
				ft_putwstr.c		\
				ft_putendl.c		\
				ft_putnbr.c			\
				ft_putchar_fd.c		\
				ft_putwchar_fd.c	\
				ft_putstr_fd.c		\
				ft_putnstr_fd.c		\
				ft_putwstr_fd.c		\
				ft_putendl_fd.c		\
				ft_putnbr_fd.c		\
				ft_tab_init.c		\
				ft_lstnew.c			\
				ft_lstdelone.c		\
				ft_lstdel.c			\
				ft_lstadd.c			\
				ft_lstiter.c		\
				ft_lstmap.c			\
				ft_lstfind.c		\
				ft_lstdelfind.c		\
				ft_lstat.c			\
				ft_lstpush.c		\
				ft_lstlen.c			\
				ft_get_next_line.c	\
				ft_sqrt.c			\
				ft_hash_string.c	\
				ft_wchar.c			\
				ft_color_rgb.c			\
				ft_color_rgb_to_int.c	\
				ft_color_rgb_op.c		\
				ft_color_rgba.c			\
				ft_color_hsv.c			\
				ft_color_hsl.c			\
				ft_color_hsv_to_rgb.c	\
				ft_clrf_rgb.c			\
				ft_clrf_rgb_op.c		\
				ft_clrf_rgb_scale.c		\
				ft_lerp.c				\
				math/ft_vec2i.c				\
				math/ft_vec2f.c				\
				math/ft_vec2d.c				\
				math/ft_vec3f.c				\
				math/ft_vec3f_op.c			\
				math/ft_vec3f_mag.c			\
				math/ft_vec3f_rot.c			\
				math/ft_vec3f_scale.c		\
				math/ft_vec3d.c				\
				math/ft_vec3d_op.c			\
				math/ft_vec3d_mag.c			\
				math/ft_vec3d_rot.c			\
				math/ft_vec3d_scale.c		\
				math/ft_vec3ld.c			\
				math/ft_matrix.c			\
				math/ft_matrix_multiply.c	\
				math/ft_matrix_translate.c	\
				math/ft_matrix_rot.c		\
				math/ft_matrix_scale.c		\
				math/ft_vec2f_add.c			\
				math/ft_vec2f_mag.c			\
				math/ft_vec2f_rot_scale.c	\
				math/ft_clampf.c			\
				math/ft_clamp.c				\
				printf/ft_printf_field.c			\
				printf/ft_printf_core.c				\
				printf/ft_printf_parse.c			\
				printf/ft_printf_parse_field.c		\
				printf/ft_printf_parse_number.c		\
				printf/ft_printf_parse_int.c		\
				printf/ft_printf_parse_char.c		\
				printf/ft_printf_parse_pointer.c	\
				printf/ft_printf_parse_string.c		\
				printf/ft_printf_parse_none.c		\
				printf/ft_printf_format_result.c	\
				printf/ft_printf_get_bracket_str.c	\
				printf/ft_sprintf.c					\
				printf/ft_snprintf.c				\
				printf/ft_asprintf.c				\
				printf/ft_dprintf.c					\
				printf/ft_printf.c					\
				array/ft_array_init.c				\
				array/ft_array_reserve.c			\
				array/ft_array_add.c				\
				array/ft_array_push_front.c			\
				array/ft_array_push_back.c			\
				array/ft_array_front.c				\
				array/ft_array_back.c				\
				array/ft_array_pop.c				\
				array/ft_array_pop_front.c			\
				array/ft_array_pop_back.c			\
				array/ft_array_free.c				\
				array/ft_array_sort.c				\
				vector/ft_vector.c							\
				vector/ft_vector_info.c						\
				vector/ft_vector_resize.c					\
				vector/ft_vector_insert.c					\
				vector/ft_vector_at.c						\
				vector/ft_vector_pop_at.c					\
				vector/ft_vector_erase.c					\
				vector/internal_ft_vector_range.c			\
				map/ft_map.c							\
				map/ft_map_insert.c						\
				map/ft_map_at.c							\
				graph/ft_graph_create_edge_table.c	\
				graph/ft_graph_poly_fill.c			\
				graph/ft_graph_env_rect.c			\
				graph/ft_graph_env_aaline.c			\
				graph/ft_graph_transform.c			\
				graph/ft_graph_env_init.c			\
				graph/ft_graph_push.c				\
				graph/ft_graph_pop.c				\
				instream/ft_input_stream.c				\
				instream/ft_input_stream_file.c			\
				file/ft_file_get_size.c			\
				file/ft_file_to_string.c		\
				fstream/internal_ft_fstream_read_more.c			\
				fstream/ft_fstream_sread_to_any_char.c			\
				fstream/ft_fstream_sread_char.c					\
				fstream/ft_fstream_read_open.c					\
				ppm/ft_ppm_file_write.c \
				ppm/ft_ppm_file_read.c \
				ppm/ft_ppm_read_header.c \
				ppm/ft_ppm_from_floats.c

SRC			=	$(CFILES:%=$(SRC_DIR)%)

OBJ			=	$(CFILES:%.c=$(OBJ_DIR)%.o)

OBJ_SUBDIR	=	$(sort $(dir $(OBJ)))

# # # # #

all				:	$(OBJ_DIR) $(NAME)

$(NAME)			:	$(OBJ)
					ar rc $(NAME) $(OBJ)
					ranlib $(NAME)

$(OBJ_DIR)%.o	:	$(SRC_DIR)%.c
					$(CC) $(CFLAGS) -I$(INC_DIR) -MMD -MP -c $< -o $@

$(OBJ_DIR)		:
					mkdir -p $(OBJ_DIR)
					mkdir -p $(OBJ_SUBDIR)

clean			:
						$(RM) $(OBJ_DIR)

fclean			:	clean
						$(RM) $(NAME)

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

.PHONY : all, test, subdirs, clean, fclean, re, norm
