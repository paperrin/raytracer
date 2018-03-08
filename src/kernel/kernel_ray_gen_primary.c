/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernel_ray_gen_primary.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 21:50:02 by paperrin          #+#    #+#             */
/*   Updated: 2018/03/16 21:41:36 by tlernoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			kernel_ray_gen_primary_create(t_app *app)
{
	cl_uint2			screen_size;

	app->kernel_ray_gen.work_size = app->win.width * app->win.height * app->config.samples_width * app->config.samples_width;
	if (!opencl_kernel_create_n_args(&app->kernel_ray_gen, &app->ocl, 4))
		return (0);
	if (!opencl_kernel_load_from_file(&app->kernel_ray_gen
				, "./src/cl/kernel_ray_gen_primary.cl", "-I ./include/"))
		return (0);
	screen_size.s[0] = app->win.width;
	screen_size.s[1] = app->win.height;
	opencl_kernel_arg_select_id(&app->kernel_ray_gen, 0);
	if (!opencl_kernel_arg_selected_create(&app->kernel_ray_gen
				, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR
				, sizeof(screen_size), (void*)&screen_size))
		return (0);
	return (1);
}

int			kernel_ray_gen_primary_launch(t_app *app)
{
	static size_t	old_work_size = 0;
	cl_int			err;

	app->n_rays = app->kernel_ray_gen.work_size;
	if (app->kernel_ray_gen.work_size > old_work_size)
	{
		old_work_size = app->kernel_ray_gen.work_size;
		opencl_kernel_arg_select_id(&app->kernel_ray_gen, 2);
		opencl_kernel_arg_selected_destroy(&app->kernel_ray_gen);
		if (!opencl_kernel_arg_selected_create(&app->kernel_ray_gen
				, CL_MEM_READ_WRITE
				, sizeof(t_ray_state) * app->kernel_ray_gen.work_size, NULL))
			return (0);
	}
	opencl_kernel_arg_select_id(&app->kernel_ray_gen, 1);
	opencl_kernel_arg_selected_destroy(&app->kernel_ray_gen);
	if (!opencl_kernel_arg_selected_create(&app->kernel_ray_gen
				, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR
				, sizeof(app->cam.cam_data), (void*)&app->cam.cam_data))
		return (0);
	opencl_kernel_arg_select_id(&app->kernel_ray_gen, 3);
	opencl_kernel_arg_selected_destroy(&app->kernel_ray_gen);
	if (!opencl_kernel_arg_selected_create(&app->kernel_ray_gen
			, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR
			, sizeof(t_config), (void*)&app->config))
		return (0);
	if (CL_SUCCESS != (err = clEnqueueNDRangeKernel(app->ocl.cmd_queue, app->kernel_ray_gen.kernel, 1, NULL
			, &app->kernel_ray_gen.work_size, NULL, 0, NULL, NULL)))
		return (error_cl_code(err));
	return (1);
}

void		kernel_ray_gen_primary_destroy(t_app *app)
{
	opencl_kernel_destroy(&app->kernel_ray_gen);
}
