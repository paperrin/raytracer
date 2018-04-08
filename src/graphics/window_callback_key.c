/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_callback_key.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 15:49:36 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/08 21:53:02 by ilarbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

static void			f_callback_key(GLFWwindow *glfw_win, int key, int scancode,
		int action, int mods)
{
	t_window		*win;

	(void)scancode;
	(void)mods;
	win = (t_window*)glfwGetWindowUserPointer(glfw_win);
	if (!win->f_callback_key)
		return ;
	(*win->f_callback_key)(win->user_ptr, key, action);
}

void				window_callback_key(t_window *win,
		t_f_window_callback_key f_callback)
{
	win->f_callback_key = f_callback;
	glfwSetKeyCallback(win->glfw_win, &f_callback_key);
}
