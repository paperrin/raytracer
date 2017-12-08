/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_callback_mouse_button.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 15:55:37 by paperrin          #+#    #+#             */
/*   Updated: 2017/12/04 16:26:18 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

static void			f_callback_mouse_button(GLFWwindow *glfw_win,
		int button, int action, int mods)
{
	t_window		*win;

	(void)mods;
	win = (t_window*)glfwGetWindowUserPointer(glfw_win);
	if (!win->f_callback_mouse_button)
		return ;
	(*win->f_callback_mouse_button)(win->user_ptr, button, action);
}

void				window_callback_mouse_button(t_window *win,
		t_f_window_callback_mouse_button f_callback)
{
	win->f_callback_mouse_button = f_callback;
	glfwSetMouseButtonCallback(win->glfw_win, &f_callback_mouse_button);
}
