/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernel_ray_shade.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 22:37:07 by paperrin          #+#    #+#             */
/*   Updated: 2018/01/16 23:14:38 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				kernel_ray_shade_create(t_app *app)
{
	app->kernel_ray_shade.work_size = APP_WIDTH * APP_HEIGHT;
	if (!opencl_kernel_create_n_args(&app->kernel_ray_shade, &app->ocl, 6))
		return (0);
	if (!opencl_kernel_load_from_file(&app->kernel_ray_shade
				, "./src/cl/kernel_ray_shade.cl", "-I ./include/ -I ./src/cl/"))
		return (0);
	opencl_kernel_arg_select_id(&app->kernel_ray_shade, 0);
	opencl_kernel_arg_selected_use_kernel_arg_id(&app->kernel_ray_shade
				, &app->kernel_ray_trace, 0);
	opencl_kernel_arg_select_id(&app->kernel_ray_shade, 1);
	opencl_kernel_arg_selected_use_kernel_arg_id(&app->kernel_ray_shade
				, &app->kernel_ray_trace, 1);
	opencl_kernel_arg_select_id(&app->kernel_ray_shade, 4);
	if (!opencl_kernel_arg_selected_create(&app->kernel_ray_shade
			, CL_MEM_WRITE_ONLY
			, sizeof(cl_float) * 4 * APP_WIDTH * APP_HEIGHT, NULL))
		return (0);
	return (1);
}

int				kernel_ray_shade_launch(t_app *app)
{
	size_t		work_size;

	ft_bzero(app->draw_buf.pixels, sizeof(t_clrf_rgb) * APP_WIDTH * APP_HEIGHT);
	if (app->n_hits < 1)
		return (1);
	app->kernel_ray_shade.work_size = app->n_hits;
	work_size = app->kernel_ray_shade.work_size;
	opencl_kernel_arg_select_id(&app->kernel_ray_shade, 2);
	opencl_kernel_arg_selected_use_kernel_arg_id(&app->kernel_ray_shade
				, &app->kernel_ray_gen, 2);
	opencl_kernel_arg_select_id(&app->kernel_ray_shade, 3);
	opencl_kernel_arg_selected_use_kernel_arg_id(&app->kernel_ray_shade
			, &app->kernel_ray_trace, 3);
	clEnqueueNDRangeKernel(app->ocl.cmd_queue, app->kernel_ray_shade.kernel
			, 1, 0, &work_size, 0, 0, 0, 0);
	clEnqueueReadBuffer(app->ocl.cmd_queue, app->kernel_ray_shade.args[4]
			, CL_TRUE, 0, sizeof(cl_float) * 4 * APP_WIDTH * APP_HEIGHT, app->draw_buf.pixels, 0, NULL, NULL);
	return (1);
}

void		kernel_ray_shade_destroy(t_app *app)
{
	opencl_kernel_destroy(&app->kernel_ray_shade);
}
