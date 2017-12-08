/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_callback_mouse_scroll.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 15:55:38 by paperrin          #+#    #+#             */
/*   Updated: 2017/12/04 16:24:15 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

static void			f_callback_mouse_scroll(GLFWwindow *glfw_win,
		double x, double y)
{
	t_window		*win;

	win = (t_window*)glfwGetWindowUserPointer(glfw_win);
	if (!win->f_callback_mouse_scroll)
		return ;
	(*win->f_callback_mouse_scroll)(win->user_ptr, x, y);
}

void				window_callback_mouse_scroll(t_window *win,
		t_f_window_callback_mouse_scroll f_callback)
{
	win->f_callback_mouse_scroll = f_callback;
	glfwSetScrollCallback(win->glfw_win, &f_callback_mouse_scroll);
}
