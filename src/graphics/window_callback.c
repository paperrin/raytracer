/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_callback.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 19:14:30 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/27 15:55:29 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

void				window_callback_loop(t_window *win,
		void (*f_loop)(void*, double), void *user_ptr)
{
	double		last_time;
	double		now;

	win->user_ptr = user_ptr;
	glfwSetWindowUserPointer(win->glfw_win, win);
	now = glfwGetTime();
	last_time = now;
	win->should_close = 0;
	while (!win->should_close)
	{
		win->should_close = glfwWindowShouldClose(win->glfw_win);
		now = glfwGetTime();
		if (f_loop)
			(*f_loop)(user_ptr, (now - last_time));
		last_time = now;
		if (f_loop)
			glfwPollEvents();
		else
			glfwWaitEvents();
	}
}
