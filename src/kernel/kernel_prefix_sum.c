/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernel_prefix_sum.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlernoul <tlernoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 19:01:53 by tlernoul          #+#    #+#             */
/*   Updated: 2018/03/18 23:39:52 by tlernoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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
	if (CL_SUCCESS != (err = clGetKernelWorkGroupInfo(
			app->kernel_prefix_sum.kernel, app->ocl.device,
			CL_KERNEL_PREFERRED_WORK_GROUP_SIZE_MULTIPLE,
			sizeof(app->kernel_prefix_sum.wg_size),
			(void*)&app->kernel_prefix_sum.wg_size, NULL)))
		return (error_cl_code(err));
	if (CL_SUCCESS != (err = clSetKernelArg(app->kernel_prefix_sum.kernel, 3, sizeof(t_ray_state) * app->kernel_prefix_sum.wg_size, NULL)))
		return (error_cl_code(err));
	return (1);
}

int				kernel_prefix_sum_launch(t_app *app)
{
	t_prefix_sums	prefix_sums;

	if (!app->n_rays || !app->should_sort_rays)
		return (1);
	opencl_kernel_arg_select_id(&app->kernel_prefix_sum, 0);
	if (!opencl_kernel_arg_selected_use_kernel_arg_id(&app->kernel_prefix_sum
				, &app->kernel_ray_trace, 4))
		return (0);
	if (CL_SUCCESS != (errcode = clEnqueueNDRangeKernel(app->ocl.cmd_queue, app->kernel_prefix_sum.kernel
			, 1, NULL, &app->kernel_prefix_sum.work_size, NULL, 0, NULL, NULL)))
		return (error_cl_code(errcode));
	return (1);
}

void		kernel_prefix_sum_destroy(t_app *app)
{
	opencl_kernel_destroy(&app->kernel_prefix_sum);
}
