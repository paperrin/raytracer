/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernel_ray_shade.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/16 22:37:07 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/27 13:57:08 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				kernel_ray_shade_create(t_app *app)
{
	app->kernel_ray_shade.work_size = app->win.width * app->win.height;
	if (!opencl_kernel_create_n_args(&app->kernel_ray_shade, &app->ocl, 15))
		return (0);
	if (!opencl_kernel_load_from_file(&app->kernel_ray_shade
				, "./src/cl/kernel_ray_shade.cl", "-I ./include/ -I ./src/cl/"))
		return (0);
	if (!kernel_ray_shade_args(app))
		return (0);
	return (1);
}

int				kernel_ray_shade_launch(t_app *app)
{
	cl_int		err;

	app->n_rays = 0;
	app->kernel_ray_shade.work_size = app->win.width * app->win.height
		* app->config.samples_width * app->config.samples_width
		* pow(2, app->config.cur_depth)
		* (app->cam.cam_data.is_anaglyph + 1);
	if ((err = clEnqueueWriteBuffer(app->ocl.cmd_queue
					, app->kernel_ray_shade.args[11]
			, CL_TRUE, 0, sizeof(cl_uint), &app->n_rays, 0, NULL, NULL))
			!= CL_SUCCESS)
		return (error_cl_code(err));
	if ((err = clEnqueueNDRangeKernel(app->ocl.cmd_queue
					, app->kernel_ray_shade.kernel
			, 1, NULL, &app->kernel_ray_shade.work_size, NULL, 0, NULL, NULL))
			!= CL_SUCCESS)
		return (error_cl_code(err));
	if ((err = clEnqueueReadBuffer(app->ocl.cmd_queue
					, app->kernel_ray_shade.args[11]
			, CL_TRUE, 0, sizeof(cl_uint), &app->n_rays, 0, NULL, NULL))
			!= CL_SUCCESS)
		return (error_cl_code(err));
	return (-1);
}

void			kernel_ray_shade_destroy(t_app *app)
{
	opencl_kernel_destroy(&app->kernel_ray_shade);
}
