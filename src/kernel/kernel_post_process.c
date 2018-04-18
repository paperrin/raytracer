/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernel_post_process.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlernoul <tlernoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 23:33:13 by tlernoul          #+#    #+#             */
/*   Updated: 2018/04/18 03:15:26 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			kernel_post_process_create(t_app *app)
{
	app->kernel_post_process.work_size = app->kernel_clear.work_size;
	if (!opencl_kernel_create_n_args(&app->kernel_post_process, &app->ocl, 2))
		return (0);
	if (!opencl_kernel_load_from_file(&app->kernel_post_process,
				"./src/cl/kernel_post_process.cl", "-I ./include/"))
		return (0);
	opencl_kernel_arg_select_id(&app->kernel_post_process, 0);
	if (!opencl_kernel_arg_selected_use_kernel_arg_id(&app->kernel_post_process
				, &app->kernel_clear, 0))
		return (0);
	opencl_kernel_arg_select_id(&app->kernel_post_process, 1);
	if (!opencl_kernel_arg_selected_use_kernel_arg_id(&app->kernel_post_process
				, &app->kernel_ray_gen, 0))
		return (0);
	return (1);
}

int			kernel_post_process_launch(t_app *app)
{
	cl_int	err;

	if ((err = clEnqueueNDRangeKernel(app->ocl.cmd_queue
					, app->kernel_post_process.kernel, 1, NULL
			, &app->kernel_post_process.work_size, NULL, 0, NULL, NULL))
					!= CL_SUCCESS)
		return (error_cl_code(err));
	return (1);
}

void		kernel_post_process_destroy(t_app *app)
{
	opencl_kernel_destroy(&app->kernel_post_process);
}
