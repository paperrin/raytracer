/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernel_combine_texels.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 00:52:15 by paperrin          #+#    #+#             */
/*   Updated: 2018/01/15 02:16:22 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				kernel_combine_texels_create(t_app *app)
{
	if (!opencl_kernel_create_n_args(&app->kernel_combine_texels, &app->ocl, 4))
		return (0);
	if (!opencl_kernel_load_from_file(&app->kernel_combine_texels
				, "./src/cl/kernel_combine_texels.cl", "-I ./include/"))
		return (0);
	opencl_kernel_arg_select_id(&app->kernel_combine_texels, 0);
	opencl_kernel_arg_selected_use_kernel_arg_id(&app->kernel_combine_texels
			, &app->kernel_ray_gen, 0);
	opencl_kernel_arg_select_id(&app->kernel_combine_texels, 3);
	if (!opencl_kernel_arg_selected_create(&app->kernel_combine_texels
			, CL_MEM_WRITE_ONLY
			, sizeof(t_clrf_rgb) * APP_WIDTH * APP_HEIGHT, NULL))
		return (0);
	return (1);
}

int				kernel_combine_texels_launch(t_app *app)
{
	size_t		work_size;

	ft_bzero(app->draw_buf.pixels, sizeof(t_clrf_rgb) * APP_WIDTH * APP_HEIGHT);
	app->kernel_combine_texels.work_size = APP_WIDTH * APP_HEIGHT;
	work_size = app->kernel_combine_texels.work_size;
	opencl_kernel_arg_select_id(&app->kernel_combine_texels, 1);
	opencl_kernel_arg_selected_use_kernel_arg_id(&app->kernel_combine_texels
				, &app->kernel_compute_texels, 5);
	opencl_kernel_arg_select_id(&app->kernel_combine_texels, 2);
	opencl_kernel_arg_selected_use_kernel_arg_id(&app->kernel_combine_texels
				, &app->kernel_ray_trace, 4);
	clEnqueueNDRangeKernel(app->ocl.cmd_queue, app->kernel_combine_texels.kernel
			, 1, 0, &work_size, 0, 0, 0, 0);
	clEnqueueReadBuffer(app->ocl.cmd_queue, app->kernel_combine_texels.args[3]
			, CL_TRUE, 0, sizeof(cl_float) * APP_WIDTH * APP_HEIGHT * 4, app->draw_buf.pixels, 0, NULL, NULL);
	return (1);
}

void		kernel_combine_texels_destroy(t_app *app)
{
	opencl_kernel_destroy(&app->kernel_combine_texels);
}
