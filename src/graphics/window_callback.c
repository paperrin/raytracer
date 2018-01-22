/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_callback.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 19:14:30 by paperrin          #+#    #+#             */
/*   Updated: 2018/01/20 18:57:12 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

void				window_callback_loop(t_window *win,
		void (*f_loop)(void*, double), void *user_ptr)
{
	double		last_time;

	win->user_ptr = user_ptr;
	glfwSetWindowUserPointer(win->glfw_win, win);
	last_time = glfwGetTime();
	win->should_close = 0;
	while (!win->should_close)
	{
		win->should_close = glfwWindowShouldClose(win->glfw_win);
		if (f_loop)
			(*f_loop)(user_ptr, (glfwGetTime() - last_time) * 1000);
		if (f_loop)
			glfwPollEvents();
		else
			glfwWaitEvents();
		last_time = glfwGetTime();
	}
}
