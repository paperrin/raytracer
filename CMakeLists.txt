# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    CMakeLists.txt                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: paperrin <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/04 23:22:26 by paperrin          #+#    #+#              #
#    Updated: 2017/12/06 22:25:40 by paperrin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

cmake_minimum_required(VERSION 2.8)

project(rtv1)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

find_package(OpenGL REQUIRED)
if (NOT ${OPENGL_FOUND})
	message("OpenGL not found")
endif()

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/glfw)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libft)

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${CMAKE_CURRENT_SOURCE_DIR}/libft/include
	${CMAKE_CURRENT_SOURCE_DIR}/glfw/include
	${OPENGL_INCLUDE_DIR}
)

SET(SRC_FILES
	src/graphics/window.c
	src/graphics/window_render.c
	src/graphics/window_callback.c
	src/graphics/window_callback_key.c
	src/graphics/window_callback_mouse_motion.c
	src/graphics/window_callback_mouse_button.c
	src/graphics/window_callback_mouse_scroll.c
	src/graphics/image.c
	src/objs/obj_f.c
	src/objs/obj_sphere.c
	src/objs/obj_cylinder.c
	src/objs/obj_plane.c
	src/camera/camera.c
	src/camera/camera_render.c
	src/main.c
	src/event.c
	src/render.c
	src/solve_quadratic.c
)
add_executable(rtv1 ${SRC_FILES})

target_link_libraries(rtv1
	ft
	glfw
	${OPENGL_LIBRARY}
	${OPENGL_glu_LIBRARY}
)
