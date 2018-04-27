/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernel_ray_gen_primary.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 21:50:02 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/27 13:37:11 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			kernel_ray_gen_primary_create(t_app *app)
{
	if (!opencl_kernel_create_n_args(&app->kernel_ray_gen, &app->ocl, 3))
		return (0);
	app->kernel_ray_gen.work_size = app->win.width * app->win.height
			* app->config.samples_width * app->config.samples_width
			* (app->cam.cam_data.is_anaglyph + 1);
	if (!opencl_kernel_load_from_file(&app->kernel_ray_gen
				, "./src/cl/kernel_ray_gen_primary.cl"
				, "-I ./include/ -I ./src/cl/"))
		return (0);
	opencl_kernel_arg_select_id(&app->kernel_ray_gen, 0);
	if (!opencl_kernel_arg_selected_create(&app->kernel_ray_gen
			, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR
			, sizeof(t_config), (void*)&app->config))
		return (0);
	opencl_kernel_arg_select_id(&app->kernel_ray_gen, 1);
	if (!opencl_kernel_arg_selected_create(&app->kernel_ray_gen
			, CL_MEM_READ_ONLY, sizeof(app->cam.cam_data), NULL))
		return (0);
	opencl_kernel_arg_select_id(&app->kernel_ray_gen, 2);
	if (!opencl_kernel_arg_selected_create(&app->kernel_ray_gen
			, CL_MEM_READ_WRITE
			, sizeof(t_ray_state) * app->kernel_ray_gen.work_size
				* pow(2, app->config.max_depth), NULL))
		return (0);
	return (1);
}

int			kernel_ray_gen_primary_launch(t_app *app)
{
	cl_int		err;

	app->n_rays = app->kernel_ray_gen.work_size;
	if (!update_gpu_config(app))
		return (0);
	if ((err = clEnqueueWriteBuffer(app->ocl.cmd_queue,
			app->kernel_ray_gen.args[1], CL_TRUE, 0, sizeof(app->cam.cam_data),
			(void*)&app->cam.cam_data, 0, NULL, NULL)) != CL_SUCCESS)
		return (error_cl_code(err));
	if ((err = clEnqueueNDRangeKernel(app->ocl.cmd_queue
					, app->kernel_ray_gen.kernel, 1, NULL
			, &app->kernel_ray_gen.work_size, NULL, 0, NULL, NULL))
			!= CL_SUCCESS)
		return (error_cl_code(err));
	return (1);
}

int			update_gpu_config(t_app *app)
{
	cl_int		err;

	if ((err = clEnqueueWriteBuffer(app->ocl.cmd_queue,
			app->kernel_ray_gen.args[0], CL_TRUE, 0, sizeof(t_config),
			(void*)&app->config, 0, NULL, NULL)) != CL_SUCCESS)
		return (error_cl_code(err));
	return (1);
}

void		kernel_ray_gen_primary_destroy(t_app *app)
{
	opencl_kernel_destroy(&app->kernel_ray_gen);
}
