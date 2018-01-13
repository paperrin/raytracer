/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback_key.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 16:52:27 by paperrin          #+#    #+#             */
/*   Updated: 2018/01/13 23:32:01 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		callback_key(void *user_ptr, int key, int action)
{
	t_app	*app;

	(void)action;
	app = (t_app*)user_ptr;
	if (key == GLFW_KEY_ESCAPE)
		app_destroy(app, EXIT_SUCCESS);
	else if (key == GLFW_KEY_A || key == GLFW_KEY_D)
		camera_translate_x(&app->cam, key == GLFW_KEY_A ? -0.05 : 0.05);
	else if (key == GLFW_KEY_R || key == GLFW_KEY_F)
		camera_translate_y(&app->cam, key == GLFW_KEY_F ? -0.05 : 0.05);
	else if (key == GLFW_KEY_W || key == GLFW_KEY_S)
		camera_translate_z(&app->cam, key == GLFW_KEY_S ? -0.05 : 0.05);
	else if (key == GLFW_KEY_I || key == GLFW_KEY_K)
		camera_rotation_x(&app->cam, key == GLFW_KEY_I ? -0.05 : 0.05);
	else if (key == GLFW_KEY_J || key == GLFW_KEY_L)
		camera_rotation_y(&app->cam, key == GLFW_KEY_L ? -0.05 : 0.05);
	else if (key == GLFW_KEY_Y || key == GLFW_KEY_H)
		camera_rotation_z(&app->cam, key == GLFW_KEY_Y ? -0.05 : 0.05);
	render(app);
}
