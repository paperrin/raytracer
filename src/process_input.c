/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 19:21:17 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/23 18:07:47 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		process_input_mouse(t_app *app, double elapsed)
{
	const double	rot = 3;
	static double	last_x = APP_WIDTH / 2;
	static double	last_y = APP_HEIGHT / 2;
	double			x;
	double			y;

	glfwGetCursorPos(app->win.glfw_win, &x, &y);
	app->config.mouse_pxl_id = (int)x + (int)y * APP_WIDTH;
	if (!app->mouse_captured)
		return ;
	if (x != last_x)
		app->cam.rot.s[1] -= rot * elapsed * ((x < last_x) * 2 - 1);
	if (y != last_y)
		app->cam.rot.s[0] -= rot * elapsed * ((y < last_y) * 2 - 1);
	last_x = x;
	last_y = y;
}

static void		process_input_key(t_app *app, double elapsed)
{
	t_vec3f			move;
	t_vec3f			rot;

	move.x = (glfwGetKey(app->win.glfw_win, GLFW_KEY_D) == GLFW_PRESS)
		- (glfwGetKey(app->win.glfw_win, GLFW_KEY_A) == GLFW_PRESS);
	move.y = (glfwGetKey(app->win.glfw_win, GLFW_KEY_R) == GLFW_PRESS)
		- (glfwGetKey(app->win.glfw_win, GLFW_KEY_F) == GLFW_PRESS);
	move.z = (glfwGetKey(app->win.glfw_win, GLFW_KEY_W) == GLFW_PRESS)
		- (glfwGetKey(app->win.glfw_win, GLFW_KEY_S) == GLFW_PRESS);
	move = ft_vec3f_scale(move, app->cam.move_speed * elapsed);
	scene_camera_translate(&app->cam, move.x, move.y, move.z);
	rot.y = (glfwGetKey(app->win.glfw_win, GLFW_KEY_L) == GLFW_PRESS)
		- (glfwGetKey(app->win.glfw_win, GLFW_KEY_J) == GLFW_PRESS);
	rot.x = (glfwGetKey(app->win.glfw_win, GLFW_KEY_K) == GLFW_PRESS)
		- (glfwGetKey(app->win.glfw_win, GLFW_KEY_I) == GLFW_PRESS);
	rot.z = (glfwGetKey(app->win.glfw_win, GLFW_KEY_U) == GLFW_PRESS)
		- (glfwGetKey(app->win.glfw_win, GLFW_KEY_O) == GLFW_PRESS);
	rot = ft_vec3f_scale(rot, app->cam.rot_speed * elapsed);
	rot = ft_vec3f_add(rot,
			ft_vec3f(app->cam.rot.s[0], app->cam.rot.s[1], app->cam.rot.s[2]));
	app->cam.rot = vec3r(rot.x, rot.y, rot.z);
}

void			process_input(t_app *app, double elapsed)
{
	process_input_mouse(app, elapsed);
	process_input_key(app, elapsed);
}
