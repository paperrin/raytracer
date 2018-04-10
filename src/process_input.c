/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 19:21:17 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/09 21:10:59 by ilarbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		process_input_mouse(t_app *app, double elapsed)
{
	const double	rot = 250;
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
	const double	move = 80;
	char			a_pressed;
	char			s_pressed;
	char			d_pressed;
	char			w_pressed;
	char			r_pressed;
	char			f_pressed;
	const double	rot = 250;
	char			j_pressed;
	char			l_pressed;
	char			i_pressed;
	char			k_pressed;
	char			y_pressed;
	char			h_pressed;

	a_pressed = glfwGetKey(app->win.glfw_win, GLFW_KEY_A) == GLFW_PRESS;
	s_pressed = glfwGetKey(app->win.glfw_win, GLFW_KEY_S) == GLFW_PRESS;
	d_pressed = glfwGetKey(app->win.glfw_win, GLFW_KEY_D) == GLFW_PRESS;
	w_pressed = glfwGetKey(app->win.glfw_win, GLFW_KEY_W) == GLFW_PRESS;
	r_pressed = glfwGetKey(app->win.glfw_win, GLFW_KEY_R) == GLFW_PRESS;
	f_pressed = glfwGetKey(app->win.glfw_win, GLFW_KEY_F) == GLFW_PRESS;
	if (a_pressed || d_pressed)
		camera_translate_x(&app->cam, (d_pressed - a_pressed) * move * elapsed);
	if (r_pressed || f_pressed)
		camera_translate_y(&app->cam, (r_pressed - f_pressed) * move * elapsed);
	if (w_pressed || s_pressed)
		camera_translate_z(&app->cam, (w_pressed - s_pressed) * move * elapsed);
	j_pressed = glfwGetKey(app->win.glfw_win, GLFW_KEY_J) == GLFW_PRESS;
	l_pressed = glfwGetKey(app->win.glfw_win, GLFW_KEY_L) == GLFW_PRESS;
	i_pressed = glfwGetKey(app->win.glfw_win, GLFW_KEY_I) == GLFW_PRESS;
	k_pressed = glfwGetKey(app->win.glfw_win, GLFW_KEY_K) == GLFW_PRESS;
	y_pressed = glfwGetKey(app->win.glfw_win, GLFW_KEY_Y) == GLFW_PRESS;
	h_pressed = glfwGetKey(app->win.glfw_win, GLFW_KEY_H) == GLFW_PRESS;
	if (j_pressed || l_pressed)
		app->cam.rot.s[1] += (l_pressed - j_pressed) * rot * elapsed;
	if (i_pressed || k_pressed)
		app->cam.rot.s[0] += (k_pressed - i_pressed) * rot * elapsed;
	if (y_pressed || h_pressed)
		app->cam.rot.s[2] += (h_pressed - y_pressed) * rot * elapsed;
}

void			process_input(t_app *app, double elapsed)
{
	process_input_mouse(app, elapsed);
	process_input_key(app, elapsed);
}
