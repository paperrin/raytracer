/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 17:46:24 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/12 15:24:43 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"

static void		callback_error(int error, const char *desc)
{
	(void)error;
	ft_dprintf(STDERR_FILENO, "Error: %s\n", desc);
}

int				window_create(t_window *win, unsigned int width,
		unsigned int height, char *title)
{
	glfwSetErrorCallback(&callback_error);
	if (!glfwInit())
		return (0);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	if (!(win->glfw_win = glfwCreateWindow(width, height, title, NULL, NULL)))
	{
		glfwTerminate();
		return (0);
	}
	glfwMakeContextCurrent(win->glfw_win);
	glfwSwapInterval(1);
	glfwGetFramebufferSize(win->glfw_win, &win->width, &win->height);
	glViewport(0, 0, win->width, win->height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, win->width, win->height, 0, -1, 1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	return (1);
}

void			window_destroy(t_window *win)
{
	glfwDestroyWindow(win->glfw_win);
	glfwTerminate();
}

void			window_loop(t_window *win, void *user_ptr)
{
	window_callback_loop(win, NULL, user_ptr);
}
