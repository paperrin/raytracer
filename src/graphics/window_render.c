/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 20:33:21 by paperrin          #+#    #+#             */
/*   Updated: 2017/12/04 20:33:48 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

void			window_clear(t_window *win, t_clrf_rgb color)
{
	glfwMakeContextCurrent(win->glfw_win);
	glClearColor(color.r, color.g, color.b, 1);
	glClear(GL_COLOR_BUFFER_BIT);
}

void			window_swap_buffers(t_window *win)
{
	glfwSwapBuffers(win->glfw_win);
}
