# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    CMakeLists.txt                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: paperrin <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/04 23:22:26 by paperrin          #+#    #+#              #
#    Updated: 2017/12/10 14:42:39 by paperrin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

cmake_minimum_required(VERSION 2.8)

project(rt)

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

	src/callbacks/callback_key.c
	
	src/main.c
)
add_executable(rt ${SRC_FILES})

target_link_libraries(rt
	ft
	glfw
	${OPENGL_LIBRARY}
	${OPENGL_glu_LIBRARY}
)
