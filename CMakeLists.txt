# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    CMakeLists.txt                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: paperrin <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/04 23:22:26 by paperrin          #+#    #+#              #
#    Updated: 2017/12/17 19:44:40 by paperrin         ###   ########.fr        #
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
	src/opencl/opencl_init.c
	src/opencl/opencl_print_device_info.c
	src/opencl/opencl_release_all.c
	src/opencl/opencl_kernel_init.c
	src/opencl/opencl_kernel_create_from_file.c
	src/opencl/opencl_kernel_destroy.c

	src/callbacks/callback_key.c

	src/vec/vec3r.c

	src/obj/obj_sphere.c

	src/main.c
	src/catch_error.c
)
files_import(
	include/shared.h
	src/cl/kernel_ray_gen_primary.cl
	src/cl/kernel_ray_trace.cl
	src/cl/kernel_compute_texels.cl
	src/cl/kernel_ray_gen_next.cl
	src/cl/kernel_combine_texels.cl
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
