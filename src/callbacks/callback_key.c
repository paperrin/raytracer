/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback_key.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 16:52:27 by paperrin          #+#    #+#             */
/*   Updated: 2018/03/17 21:44:00 by tlernoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		callback_key(void *user_ptr, int key, int action)
{
	t_app	*app;

	app = (t_app*)user_ptr;
	(void)action;
	if (key == GLFW_KEY_ESCAPE)
		app_destroy(app, EXIT_SUCCESS);
	else if (key == GLFW_KEY_M && action == GLFW_PRESS)
	{
		app->mouse_captured = !app->mouse_captured;
		if (app->mouse_captured)
			glfwSetInputMode(app->win.glfw_win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		else
			glfwSetInputMode(app->win.glfw_win, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	else if (key == GLFW_KEY_X && action == GLFW_PRESS)
		app->should_sort_rays = !app->should_sort_rays;
}
