/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernel_prefix_sum.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlernoul <tlernoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 19:01:53 by tlernoul          #+#    #+#             */
/*   Updated: 2018/03/16 22:01:24 by tlernoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int		launch_kernel(t_app *app, t_prefix_sums prefix_sums)
{
	cl_int			errcode;

	if (app->kernel_prefix_sum.work_size == 0)
		app->kernel_prefix_sum.work_size++;
	if (CL_SUCCESS != (errcode = clEnqueueWriteBuffer(app->ocl.cmd_queue, app->kernel_prefix_sum.args[1],
			CL_TRUE, 0, sizeof(t_prefix_sums), (void*)&prefix_sums, 0, NULL, NULL)))
		return (error_cl_code(errcode));
	if (CL_SUCCESS != (errcode = clEnqueueNDRangeKernel(app->ocl.cmd_queue, app->kernel_prefix_sum.kernel
			, 1, NULL, &app->kernel_prefix_sum.work_size, NULL, 0, NULL, NULL)))
		return (error_cl_code(errcode));
	return (1);
}

int				kernel_prefix_sum_create(t_app *app)
{
	if (!opencl_kernel_create_n_args(&app->kernel_prefix_sum, &app->ocl, 2))
		return (0);
	if (!opencl_kernel_load_from_file(&app->kernel_prefix_sum
				, "./src/cl/kernel_prefix_sum.cl", "-I ./include/"))
		return (0);
	opencl_kernel_arg_select_id(&app->kernel_prefix_sum, 1);
	if (!opencl_kernel_arg_selected_create(&app->kernel_prefix_sum
				, CL_MEM_READ_ONLY
				, sizeof(t_prefix_sums), NULL))
		return (0);
	return (1);
}

int				kernel_prefix_sum_launch(t_app *app)
{
	t_prefix_sums	prefix_sums;

	if (app->n_rays == 0)
		return (1);
	opencl_kernel_arg_select_id(&app->kernel_prefix_sum, 0);
	if (!opencl_kernel_arg_selected_use_kernel_arg_id(&app->kernel_prefix_sum
				, &app->kernel_ray_trace, 4))
		return (0);
	prefix_sums.start = 1;
	prefix_sums.step = 2;
	prefix_sums.offset = 1;
	prefix_sums.arr_size = app->n_rays;
	while (prefix_sums.start < prefix_sums.arr_size)
	{
		app->kernel_prefix_sum.work_size = (prefix_sums.arr_size - (prefix_sums.start - prefix_sums.offset)) / prefix_sums.step + 2;
		if (!launch_kernel(app, prefix_sums))
			return (0);
		prefix_sums.start = prefix_sums.start * 2 + 1;
		prefix_sums.step *= 2;
		prefix_sums.offset *= 2;
	}
	prefix_sums.start = 2;
	prefix_sums.step = 2;
	prefix_sums.offset = 1;
	while (prefix_sums.start * 2 + 1 < prefix_sums.arr_size)
	{
		prefix_sums.start = prefix_sums.start * 2 + 1;
		prefix_sums.step *= 2;
		prefix_sums.offset *= 2;
	}
	while (prefix_sums.start >= 2 )
	{
		app->kernel_prefix_sum.work_size = (prefix_sums.arr_size - (prefix_sums.start - prefix_sums.offset)) / prefix_sums.step + 2;
		if (!launch_kernel(app, prefix_sums))
			return (0);
		prefix_sums.start = (prefix_sums.start - 1) / 2;
		prefix_sums.step /= 2;
		prefix_sums.offset /= 2;
	}
	return (1);
}

void		kernel_prefix_sum_destroy(t_app *app)
{
	opencl_kernel_destroy(&app->kernel_prefix_sum);
}
