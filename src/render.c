/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 15:59:27 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/30 22:00:52 by tlernoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int		draw_kernel_screen_buffer(t_app *app)
{
	cl_int		err;

	if (CL_SUCCESS != (err = clFinish(app->ocl.cmd_queue)))
		return (error_cl_code(err));
	if (!app->config.fxaa && !app->config.post_filters)
	{
		if (CL_SUCCESS != (err = clEnqueueReadBuffer(app->ocl.cmd_queue
			, app->kernel_clear.args[0], CL_TRUE, 0
			, sizeof(cl_float) * 4 * app->win.width * app->win.height
			, app->draw_buf.pixels, 0, 0, 0)))
			return (error_cl_code(err));
	}
	else
	{
		if (CL_SUCCESS != (err = clEnqueueReadBuffer(app->ocl.cmd_queue
			, app->kernel_post_process.args[2], CL_TRUE, 0
			, sizeof(cl_float) * 4 * app->win.width * app->win.height
			, app->draw_buf.pixels, 0, 0, 0)))
			return (error_cl_code(err));
	}
	image_put(&app->draw_buf, 0, 0);
	window_swap_buffers(&app->win);
	return (1);
}

static void		try(int (*f_kernel_launch)(t_app *app),
		char const *kernel_name, t_app *app)
{
	if (!(*f_kernel_launch)(app))
	{
		if (kernel_name)
			error_string_2(kernel_name, "launch failed");
		app_destroy(app, EXIT_FAILURE);
	}
}

void			render(void *user_ptr, double elapsed)
{
	static double				last_time = -1;
	static size_t				n_frames = 0;
	t_app						*app;

	app = (t_app*)user_ptr;
	process_input(app, elapsed);
	scene_camera_update(&app->cam);
	try(&kernel_ray_gen_primary_launch, "kernel_ray_gen", app);
	try(&kernel_clear_launch, "kernel_clear", app);
	app->config.cur_depth = -1;
	while (++app->config.cur_depth <= app->config.max_depth)
	{
		try(&update_gpu_config, NULL, app);
		try(&kernel_ray_trace_launch, "kernel_ray_trace", app);
		try(&kernel_ray_shade_launch, "kernel_ray_shade", app);
	}
	try(&kernel_post_process_launch, "kernel_post_process", app);
	try(&draw_kernel_screen_buffer, NULL, app);
	if (++n_frames && glfwGetTime() - last_time > 1)
	{
		last_time = glfwGetTime();
		ft_printf("FPS: %4lu\n", n_frames);
		n_frames = 0;
	}
}
