/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernel_sum_blocks.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 02:35:26 by paperrin          #+#    #+#             */
/*   Updated: 2018/03/19 04:10:31 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				kernel_sum_blocks_create(t_app *app)
{
	if (!opencl_kernel_create_n_args(&app->kernel_sum_blocks, &app->ocl, 3))
		return (0);
	if (!opencl_kernel_load_from_file(&app->kernel_sum_blocks
				, "./src/cl/kernel_sum_blocks.cl", "-I ./include/"))
		return (0);
	return (1);
}

int				kernel_sum_blocks_launch(t_app *app)
{
	cl_int			err;

	app->kernel_sum_blocks.work_size = app->n_rays;
	opencl_kernel_arg_select_id(&app->kernel_sum_blocks, 0);
	if (!opencl_kernel_arg_selected_use_kernel_arg_id(&app->kernel_sum_blocks
				, &app->kernel_ray_trace, 4))
		return (0);
	opencl_kernel_arg_select_id(&app->kernel_sum_blocks, 1);
	if (!opencl_kernel_arg_selected_use_kernel_arg_id(&app->kernel_sum_blocks
				, &app->kernel_prefix_sum, 3))
		return (0);
	opencl_kernel_arg_select_id(&app->kernel_sum_blocks, 2);
	if (!opencl_kernel_arg_selected_use_kernel_arg_id(&app->kernel_sum_blocks
				, &app->kernel_prefix_sum, 2))
		return (0);
	if (CL_SUCCESS != (err = clEnqueueNDRangeKernel(app->ocl.cmd_queue, app->kernel_sum_blocks.kernel
			, 1, NULL, &app->kernel_sum_blocks.work_size, NULL, 0, NULL, NULL)))
		return (error_cl_code(err));
	return (1);
}

void		kernel_sum_blocks_destroy(t_app *app)
{
	opencl_kernel_destroy(&app->kernel_sum_blocks);
}
