/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernel_clear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 14:34:09 by paperrin          #+#    #+#             */
/*   Updated: 2018/01/24 15:18:47 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				kernel_clear_create(t_app *app)
{
	app->kernel_clear.work_size = APP_WIDTH * APP_HEIGHT;
	if (!opencl_kernel_create_n_args(&app->kernel_clear, &app->ocl, 1))
		return (0);
	if (!opencl_kernel_load_from_file(&app->kernel_clear
				, "./src/cl/kernel_clear.cl", "-I ./include/"))
		return (0);
	opencl_kernel_arg_select_id(&app->kernel_clear, 0);
	if (!opencl_kernel_arg_selected_create(&app->kernel_clear
			, CL_MEM_READ_WRITE
			, sizeof(cl_float) * 4 * APP_WIDTH * APP_HEIGHT, NULL))
		return (0);
	return (1);
}

int				kernel_clear_launch(t_app *app)
{
	clEnqueueNDRangeKernel(app->ocl.cmd_queue, app->kernel_clear.kernel
			, 1, NULL, &app->kernel_clear.work_size, NULL, 0, NULL, NULL);
	return (1);
}

void		kernel_clear_destroy(t_app *app)
{
	opencl_kernel_destroy(&app->kernel_clear);
}
