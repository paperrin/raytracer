/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernel_compute_texels.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/14 20:34:13 by paperrin          #+#    #+#             */
/*   Updated: 2018/01/15 02:00:19 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				kernel_compute_texels_create(t_app *app)
{
	size_t		arg_id;

	app->kernel_compute_texels.work_size = APP_WIDTH * APP_HEIGHT;
	if (!opencl_kernel_create_n_args(&app->kernel_compute_texels, &app->ocl, 6))
		return (0);
	if (!opencl_kernel_load_from_file(&app->kernel_compute_texels
				, "./src/cl/kernel_compute_texels.cl", "-I ./include/ -I ./src/cl/"))
		return (0);

	arg_id = 0;
	while (arg_id < 2)
	{
		opencl_kernel_arg_select_id(&app->kernel_compute_texels, arg_id);
		opencl_kernel_arg_selected_use_kernel_arg_id(&app->kernel_compute_texels
				, &app->kernel_ray_trace, arg_id);
		arg_id++;
	}
	opencl_kernel_arg_select_id(&app->kernel_compute_texels, 2);
	opencl_kernel_arg_selected_use_kernel_arg_id(&app->kernel_compute_texels
				, &app->kernel_ray_gen, 2);
	return (1);
}

int				kernel_compute_texels_launch(t_app *app)
{
	size_t		work_size;
	size_t		arg_id;

	if (app->n_hits < 1)
		return (1);
	app->kernel_compute_texels.work_size = app->n_hits;
	work_size = app->kernel_compute_texels.work_size;
	arg_id = 3;
	while (arg_id < 5)
	{
		opencl_kernel_arg_select_id(&app->kernel_compute_texels, arg_id);
		opencl_kernel_arg_selected_use_kernel_arg_id(&app->kernel_compute_texels
				, &app->kernel_ray_trace, arg_id);
		arg_id++;
	}
	opencl_kernel_arg_select_id(&app->kernel_compute_texels, 5);
	opencl_kernel_arg_selected_destroy(&app->kernel_compute_texels);
	if (!opencl_kernel_arg_selected_create(&app->kernel_compute_texels
			, CL_MEM_WRITE_ONLY
			, sizeof(t_texel) * app->n_hits, NULL))
		return (0);
	clEnqueueNDRangeKernel(app->ocl.cmd_queue, app->kernel_compute_texels.kernel
			, 1, 0, &work_size, 0, 0, 0, 0);
	return (1);
}

void		kernel_compute_texels_destroy(t_app *app)
{
	opencl_kernel_destroy(&app->kernel_compute_texels);
}
