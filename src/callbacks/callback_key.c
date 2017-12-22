/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callback_key.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 16:52:27 by paperrin          #+#    #+#             */
/*   Updated: 2017/12/22 18:42:18 by paperrin         ###   ########.fr       */
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
	else if (key == GLFW_KEY_A)
		app->cam.pos.s[0] -= 0.05;
	else if (key == GLFW_KEY_D)
		app->cam.pos.s[0] += 0.05;
	render(app);
}
