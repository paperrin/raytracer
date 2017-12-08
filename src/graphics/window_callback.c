/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_callback.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 19:14:30 by paperrin          #+#    #+#             */
/*   Updated: 2017/12/04 20:38:41 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

void				window_callback_loop(t_window *win,
		void (*f_loop)(void*), void *user_ptr)
{
	win->user_ptr = user_ptr;
	glfwSetWindowUserPointer(win->glfw_win, win);
	win->should_close = 0;
	while (!win->should_close)
	{
		win->should_close = glfwWindowShouldClose(win->glfw_win);
		if (f_loop)
			(*f_loop)(user_ptr);
		if (f_loop)
			glfwPollEvents();
		else
			glfwWaitEvents();
	}
}
