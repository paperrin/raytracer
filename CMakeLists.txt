# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    CMakeLists.txt                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: paperrin <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/04 23:22:26 by paperrin          #+#    #+#              #
#    Updated: 2018/04/11 00:43:10 by paperrin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

cmake_minimum_required(VERSION 2.8)

project(rt)

# \/ GLFW & OpenGL \/
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

find_package(OpenGL REQUIRED)
if (NOT ${OPENGL_FOUND})
	message("OpenGL not found")
endif()
# /\ GLFW & OpenGL /\

# \/ OpenCL \/
find_package(OpenCL REQUIRED)
if (NOT ${OPENCL_FOUND})
	message("OpenCL not found")
endif()
# /\ OpenCL /\

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/glfw)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libft)


include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${CMAKE_CURRENT_SOURCE_DIR}/libft/include
	${CMAKE_CURRENT_SOURCE_DIR}/glfw/include
	${OPENGL_INCLUDE_DIR}
	${OpenCL_INCLUDE_DIRS}
)

link_directories(
	${OpenCL_LIBRARY}
)

function(files_import)
	foreach(file ${ARGN})
		configure_file("${file}" "${file}" COPYONLY)
	endforeach()
endfunction()

SET(SRC_FILES
	src/graphics/window.c
	src/graphics/window_render.c
	src/graphics/window_callback.c
	src/graphics/window_callback_key.c
	src/graphics/window_callback_mouse_motion.c
	src/graphics/window_callback_mouse_button.c
	src/graphics/window_callback_mouse_scroll.c
	src/graphics/image.c

	src/opencl/opencl_get_device_info.c
	src/opencl/opencl_create.c
	src/opencl/opencl_kernel_destroy.c
	src/opencl/opencl_kernel_load_from_file.c
	src/opencl/opencl_kernel_load_from_file_utils.c
	src/opencl/opencl_kernel_create_n_args.c
	src/opencl/opencl_print_device_info.c
	src/opencl/opencl_destroy.c
	src/opencl/opencl_kernel_arg.c
	src/opencl/opencl_platform_utils.c
	src/opencl/opencl_device_utils.c

	src/kernel/kernel_ray_gen_primary.c
	src/kernel/kernel_ray_trace.c
	src/kernel/kernel_clear.c
	src/kernel/kernel_ray_shade.c
	src/kernel/kernel_post_process.c

	src/callbacks/callback_key.c
	src/callbacks/callback_mouse_motion.c

	src/camera/camera.c
	src/camera/camera_rotation.c
	src/camera/camera_translate.c
	src/camera/matrix_real16.c
	src/camera/matrix_real16_rot.c

	src/vec/vec3r.c
	src/vec/vec3f.c

	src/obj/obj_sphere.c
	src/obj/obj_plane.c

	src/scene_parser/cstream/cstream.c
	src/scene_parser/cstream/cstream_skip_chars.c
	src/scene_parser/tkstream/tkstream.c
	src/scene_parser/tkstream/tkstream_read_token.c
	src/scene_parser/tkstream/tkstream_read_punc.c
	src/scene_parser/tkstream/tkstream_read_str.c
	src/scene_parser/tkstream/tkstream_read_num.c
	src/scene_parser/tkstream/tkstream_read_op.c
	src/scene_parser/tkstream/tkstream_read_var.c
	src/scene_parser/token/token_destroy.c
	src/scene_parser/token/token_punc_destroy.c
	src/scene_parser/token/token_num_destroy.c
	src/scene_parser/token/token_str_destroy.c
	src/scene_parser/token/token_kw_destroy.c
	src/scene_parser/token/token_var_destroy.c
	src/scene_parser/token/token_op_destroy.c
	src/scene_parser/token/token_call_destroy.c
	src/scene_parser/token/token_bool_destroy.c
	src/scene_parser/ast/ast_parse.c
	src/scene_parser/ast/ast_parse_var.c
	src/scene_parser/ast/ast_parse_expr.c
	
	src/prompt/arg_dispatch.c
	src/prompt/arg_devices.c

	src/main.c
	src/process_input.c
	src/error.c
)
files_import(
	include/shared.h
	src/cl/atomic_add.cl
	src/cl/kernel_clear.cl
	src/cl/kernel_ray_gen_primary.cl
	src/cl/kernel_ray_shade.cl
	src/cl/kernel_ray_trace.cl
	src/cl/kernel_post_process.cl
	src/cl/light_get_dir.cl
	src/cl/obj_ray_hit.cl
	src/cl/obj_surface_color.cl
	src/cl/obj_surface_normal.cl
	src/cl/obj_surface_uv_map.cl
	src/cl/shade.cl
)
add_executable(rt ${SRC_FILES})

target_include_directories(rt
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(rt
	ft
	glfw
	${OPENGL_LIBRARY}
	${OPENGL_glu_LIBRARY}
	${OpenCL_LIBRARY}
)
