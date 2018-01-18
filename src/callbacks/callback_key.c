/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback_key.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 16:52:27 by paperrin          #+#    #+#             */
/*   Updated: 2018/01/18 23:43:26 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		callback_key(void *user_ptr, int key, int action)
{
	static int		u = 0;
	static int		d = 0;
	static int		l = 0;
	static int		r = 0;
	t_app	*app;

	app = (t_app*)user_ptr;
	if (key == GLFW_KEY_ESCAPE)
		app_destroy(app, EXIT_SUCCESS);
	else if (key == GLFW_KEY_A)
		l = action > 0;
	else if (key == GLFW_KEY_D)
		r = action > 0;
	else if (key == GLFW_KEY_W)
		u = action > 0;
	else if (key == GLFW_KEY_S)
		d = action > 0;
	app->cam.pos.s[0] += (r - l) * 0.05;
	app->cam.pos.s[1] += (u - d) * 0.05;
}
