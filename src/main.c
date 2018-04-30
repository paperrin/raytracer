/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 16:14:42 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/30 23:43:13 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	app_init(t_app *const app)
{
	srand(time(NULL));
	app->config.ambient_c = vec3f(1, 1, 1);
	app->config.ambient_i = 0.05;
	app->config.camera_light_c = vec3f(1, 1, 1);
	app->config.camera_light_i = 0;
	app->config.screen_size.s[0] = APP_WIDTH;
	app->config.screen_size.s[1] = APP_HEIGHT;
	app->config.color_epsilon = 1.f / 255;
	app->config.intersection_bias = 1e-3;
	app->config.z_far = 20000;
	app->config.samples_width = 1;
	app->config.max_depth = 0;
	app->config.fxaa = 0;
	app->config.projection_depth = 2;
	app->config.post_filters = e_post_filter_none;
	app->config.anaglyph_r[0] = vec3f(0.0, 0.7, 0.3);
	app->config.anaglyph_g[0] = vec3f(0.0, 0.0, 0.0);
	app->config.anaglyph_b[0] = vec3f(0.0, 0.0, 0.0);
	app->config.anaglyph_r[1] = vec3f(0.0, 0.0, 0.0);
	app->config.anaglyph_g[1] = vec3f(0.0, 1.0, 0.0);
	app->config.anaglyph_b[1] = vec3f(0.0, 0.0, 1.0);
}

static void	try(int (*f_kernel_create)(t_app *app),
		char const *kernel_name, t_app *app)
{
	if (!(*f_kernel_create)(app))
	{
		if (kernel_name)
			error_string_2(kernel_name, "creation failed");
		app_destroy(app, EXIT_FAILURE);
	}
}

int			app_create(t_app *app, int ac, const char **argv)
{
	if (!arg_dispatch(app, ac, argv))
		return (0);
	if (!window_create(&app->win, app->config.screen_size.s[0]
				, app->config.screen_size.s[1], APP_TITLE))
		return (0);
	if (!image_create(&app->draw_buf, app->win.width, app->win.height))
		app_destroy(app, EXIT_FAILURE);
	if (!(opencl_create(&app->ocl)))
		app_destroy(app, EXIT_FAILURE);
	try(&kernel_ray_gen_primary_create, "kernel_ray_gen", app);
	try(&kernel_ray_trace_create, "kernel_ray_trace", app);
	try(&kernel_clear_create, "kernel_clear", app);
	try(&kernel_ray_shade_create, "kernel_ray_shade", app);
	try(&kernel_post_process_create, "kernel_post_process", app);
	app->config.screen_size.s[0] = app->win.width;
	app->config.screen_size.s[1] = app->win.height;
	window_callback_key(&app->win, &callback_key);
	glfwSetInputMode(app->win.glfw_win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	app->mouse_captured = 1;
	window_callback_loop(&app->win, &render, app);
	return (1);
}

void		app_destroy(t_app *app, int exit_status)
{
	scene_destroy(&app->scene);
	kernel_ray_gen_primary_destroy(app);
	kernel_ray_trace_destroy(app);
	kernel_clear_destroy(app);
	kernel_ray_shade_destroy(app);
	kernel_post_process_destroy(app);
	opencl_destroy(&app->ocl);
	image_destroy(&app->draw_buf);
	window_destroy(&app->win);
	exit(exit_status);
}

int			main(int ac, const char **av)
{
	t_app				app;

	app_init(&app);
	if (!app_create(&app, ac, av))
		return (EXIT_FAILURE);
	app_destroy(&app, EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
