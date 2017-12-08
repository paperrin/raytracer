/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_callback_mouse_motion.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 15:55:33 by paperrin          #+#    #+#             */
/*   Updated: 2017/12/04 16:24:08 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

static void			f_callback_mouse_motion(GLFWwindow *glfw_win,
		double x, double y)
{
	t_window		*win;

	win = (t_window*)glfwGetWindowUserPointer(glfw_win);
	if (!win->f_callback_mouse_motion)
		return ;
	(*win->f_callback_mouse_motion)(win->user_ptr, x, y);
}

void				window_callback_mouse_motion(t_window *win,
		t_f_window_callback_mouse_motion f_callback)
{
	win->f_callback_mouse_motion = f_callback;
	glfwSetCursorPosCallback(win->glfw_win, &f_callback_mouse_motion);
}
