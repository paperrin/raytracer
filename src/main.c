/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 16:14:42 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/20 18:31:16 by ilarbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			app_create(t_app *app, int ac, const char **argv)
{
	if (!arg_dispatch(app, ac, argv))
		return (0);
	if (!window_create(&app->win, APP_WIDTH, APP_HEIGHT, APP_TITLE))
		return (0);
	if (!image_create(&app->draw_buf, app->win.width, app->win.height))
		app_destroy(app, EXIT_FAILURE);
	if (!(opencl_create(&app->ocl)))
		app_destroy(app, EXIT_FAILURE);
	if (!kernel_ray_gen_primary_create(app) && !error_string("error: ray gen kernel creation failed\n"))
		app_destroy(app, EXIT_FAILURE);
	if (!kernel_ray_trace_create(app) && !error_string("error: trace kernel creation failed\n"))
		app_destroy(app, EXIT_FAILURE);
	if (!kernel_clear_create(app) && !error_string("error: clear kernel creation failed\n"))
		app_destroy(app, EXIT_FAILURE);
	if (!kernel_ray_shade_create(app) && !error_string("error: shade kernel creation failed\n"))
		app_destroy(app, EXIT_FAILURE);
	if (!kernel_post_process_create(app) && !error_string("error: post process kernel creation failed\n"))
		app_destroy(app, EXIT_FAILURE);
	app->config.screen_size.s[0] = app->win.width;
	app->config.screen_size.s[1] = app->win.height;
	window_callback_key(&app->win, &callback_key);
	window_callback_mouse_motion(&app->win, &callback_mouse_motion);
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

void		render(void *user_ptr, double elapsed)
{
	static double			last_time = -1;
	static unsigned long		hits_per_sec = 0;
	static unsigned long		rays_per_sec = 0;
	static size_t			n_frames = 0;
	t_app				*app;
	cl_int				err;

	app = (t_app*)user_ptr;
	process_input(app, (last_time < 0) ? 0 : elapsed);
	scene_camera_update(&app->cam);
	if (!kernel_ray_gen_primary_launch(app) && !error_string("error: ray gen kernel launch failed\n"))
		app_destroy(app, EXIT_FAILURE);
	if (!kernel_clear_launch(app) && !error_string("error: clear kernel launch failed\n"))
		app_destroy(app, EXIT_FAILURE);
	app->config.cur_depth = -1;
	while (++app->config.cur_depth <= app->config.max_depth)
	{
		if (!update_gpu_config(app))
			app_destroy(app, EXIT_FAILURE);
		if (!kernel_ray_trace_launch(app) && !error_string("error: trace kernel launch failed\n"))
			app_destroy(app, EXIT_FAILURE);
		hits_per_sec += app->n_hits;
		rays_per_sec += app->n_rays;
		if (!kernel_ray_shade_launch(app) && !error_string("error: shade kernel launch failed\n"))
			app_destroy(app, EXIT_FAILURE);
		if (!kernel_post_process_launch(app) && !error_string("error: post process kernel launch failed\n"))
			app_destroy(app, EXIT_FAILURE);
	}
	clFinish(app->ocl.cmd_queue);
	if (CL_SUCCESS != (err = clEnqueueReadBuffer(app->ocl.cmd_queue, app->kernel_clear.args[0]
			, CL_TRUE, 0, sizeof(cl_float) * 4 * app->win.width * app->win.height
			, app->draw_buf.pixels, 0, 0, 0)))
	{
		error_cl_code(err);
		app_destroy(app, EXIT_FAILURE);
	}
	image_put(&app->draw_buf, 0, 0);
	window_swap_buffers(&app->win);
	n_frames++;
	if (glfwGetTime() - last_time > 1)
	{
		last_time = glfwGetTime();
		printf("FPS: %4lu   |   Rays: %10u   |   Rays/ms: %10lu    |    Secondary: %10lu\n", n_frames, app->n_hits, hits_per_sec / 1000, rays_per_sec / 1000);
		n_frames = 0;
		hits_per_sec = 0;
		rays_per_sec = 0;
	}
}

int			main(int ac, const char **av)
{
	t_app				app;

	(void)ac;
	if (!app_create(&app, ac, av))
		return (EXIT_FAILURE);
	app_destroy(&app, EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
