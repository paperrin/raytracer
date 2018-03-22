/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernel_prefix_sum.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlernoul <tlernoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 19:01:53 by tlernoul          #+#    #+#             */
/*   Updated: 2018/03/22 02:16:55 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				kernel_prefix_sum_create(t_app *app)
{
	cl_int			n;
	cl_int			err;

	if (!opencl_kernel_create_n_args(&app->kernel_prefix_sum, &app->ocl, 4))
		return (0);
	if (!opencl_kernel_load_from_file(&app->kernel_prefix_sum
				, "./src/cl/kernel_prefix_sum.cl", "-I ./include/"))
		return (0);
	if (CL_SUCCESS != (err = clGetKernelWorkGroupInfo(
			app->kernel_prefix_sum.kernel, app->ocl.device,
			CL_KERNEL_PREFERRED_WORK_GROUP_SIZE_MULTIPLE,
			sizeof(app->kernel_prefix_sum.wg_size),
			(void*)&app->kernel_prefix_sum.wg_size, NULL)))
		return (error_cl_code(err));
	n = app->kernel_prefix_sum.wg_size * 2;
	if (CL_SUCCESS != (err = clSetKernelArg(app->kernel_prefix_sum.kernel, 1,
					sizeof(cl_uint) * n, NULL)))
		return (error_cl_code(err));
	opencl_kernel_arg_select_id(&app->kernel_prefix_sum, 2);
	if (!opencl_kernel_arg_selected_create(&app->kernel_prefix_sum
				, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR
				, sizeof(cl_int), (void*)&n))
		return (0);
	if (!kernel_sum_blocks_create(app))
		return (0);
	return (1);
}

int				kernel_prefix_sum_launch(t_app *app)
{
	cl_int			err;
	int				block_sum_size;
	cl_uint			*block_sums;
	int				i;

	if (!app->n_rays || !app->should_sort_rays)
		return (1);
	app->kernel_prefix_sum.work_size = app->n_rays / 2;
	if (app->kernel_prefix_sum.work_size % app->kernel_prefix_sum.wg_size)
		app->kernel_prefix_sum.work_size = app->kernel_prefix_sum.work_size - (app->kernel_prefix_sum.work_size % app->kernel_prefix_sum.wg_size)
			+ app->kernel_prefix_sum.wg_size;
	opencl_kernel_arg_select_id(&app->kernel_prefix_sum, 3);
	opencl_kernel_arg_selected_destroy(&app->kernel_prefix_sum);
	if (!opencl_kernel_arg_selected_create(&app->kernel_prefix_sum
			, CL_MEM_READ_WRITE
			, sizeof(cl_uint) * (app->kernel_prefix_sum.work_size
				/ app->kernel_prefix_sum.wg_size), NULL))
		return (0);
	opencl_kernel_arg_select_id(&app->kernel_prefix_sum, 0);
	if (!opencl_kernel_arg_selected_use_kernel_arg_id(&app->kernel_prefix_sum
				, &app->kernel_ray_trace, 4))
		return (0);
	if (CL_SUCCESS != (err = clEnqueueNDRangeKernel(app->ocl.cmd_queue, app->kernel_prefix_sum.kernel
			, 1, NULL, &app->kernel_prefix_sum.work_size, &app->kernel_prefix_sum.wg_size, 0, NULL, NULL)))
		return (error_cl_code(err));
	/*
	 * TO REPLACE >>
	*/
	block_sum_size = app->kernel_prefix_sum.work_size / app->kernel_prefix_sum.wg_size;
	if (!(block_sums = (cl_uint*)malloc(sizeof(*block_sums) * block_sum_size)))
		return (0);
	if (CL_SUCCESS != (err = clEnqueueReadBuffer(app->ocl.cmd_queue,
					app->kernel_prefix_sum.args[3], CL_TRUE, 0,
					sizeof(cl_uint) * block_sum_size, (void*)block_sums, 0, NULL, NULL)))
	{
		if (block_sums)
			free(block_sums);
		return (error_cl_code(err));
	}
	i = 0;
	while (++i < block_sum_size)
		block_sums[i] += block_sums[i - 1];
	if (CL_SUCCESS != (err = clEnqueueWriteBuffer(app->ocl.cmd_queue,
					app->kernel_prefix_sum.args[3], CL_TRUE,
					0,
					sizeof(*block_sums) * block_sum_size, (void*)block_sums, 0, NULL, NULL)))
	{
		if (block_sums)
			free(block_sums);
		return (error_cl_code(err));
	}
	if (block_sums)
		free(block_sums);
	/*
	 * << TO REPLACE
	*/
	if (!kernel_sum_blocks_launch(app))
		return (0);
	return (1);
}

void		kernel_prefix_sum_destroy(t_app *app)
{
	opencl_kernel_destroy(&app->kernel_prefix_sum);
	kernel_sum_blocks_destroy(app);
}
