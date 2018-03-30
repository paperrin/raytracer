/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernel_ray_trace.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 18:06:33 by paperrin          #+#    #+#             */
/*   Updated: 2018/03/29 20:22:00 by ilarbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				kernel_ray_trace_create(t_app *app)
{
	cl_uint				objs_size;

	app->kernel_ray_trace.work_size = app->win.width * app->win.height * pow(2, app->config.cur_depth);
	if (!opencl_kernel_create_n_args(&app->kernel_ray_trace, &app->ocl, 5))
		return (0);
	if (!opencl_kernel_load_from_file(&app->kernel_ray_trace
				, "./src/cl/kernel_ray_trace.cl", "-I ./include/ -I ./src/cl/"))
		return (0);
	objs_size = ft_vector_size(&app->scene.v_obj);
	opencl_kernel_arg_select_id(&app->kernel_ray_trace, 0);
	if (!opencl_kernel_arg_selected_create(&app->kernel_ray_trace
			, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR
			, sizeof(t_obj) * objs_size, (void*)app->scene.v_obj.begin))
		return (0);
	opencl_kernel_arg_select_id(&app->kernel_ray_trace, 1);
	if (!opencl_kernel_arg_selected_create(&app->kernel_ray_trace
			, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR
			, sizeof(cl_uint), (void*)&objs_size))
		return (0);
	opencl_kernel_arg_select_id(&app->kernel_ray_trace, 3);
	if (!opencl_kernel_arg_selected_create(&app->kernel_ray_trace
			, CL_MEM_READ_WRITE
			, sizeof(cl_uint), NULL))
		return (0);
	return (1);
}

int				kernel_ray_trace_launch(t_app *app)
{
	cl_int		err;

	app->n_hits = 0;
	if (app->n_rays > 0)
	{
		app->kernel_ray_trace.work_size = app->win.width * app->win.height * app->config.samples_width * app->config.samples_width * pow(2, app->config.cur_depth);
		opencl_kernel_arg_select_id(&app->kernel_ray_trace, 2);
		opencl_kernel_arg_selected_use_kernel_arg_id(&app->kernel_ray_trace
				, &app->kernel_ray_gen, 2);
		if ((err = clEnqueueWriteBuffer(app->ocl.cmd_queue, app->kernel_ray_trace.args[3],
						CL_TRUE, 0, sizeof(cl_uint), (void*)&app->n_hits, 0, NULL, NULL)) != CL_SUCCESS)
			return (error_cl_code(err));
		opencl_kernel_arg_select_id(&app->kernel_ray_trace, 4);
		opencl_kernel_arg_selected_use_kernel_arg_id(&app->kernel_ray_trace
		, &app->kernel_ray_gen, 0);
		if ((err = clEnqueueNDRangeKernel(app->ocl.cmd_queue, app->kernel_ray_trace.kernel
				, 1, NULL, &app->kernel_ray_trace.work_size, NULL, 0, NULL, NULL)) != CL_SUCCESS)
			return (error_cl_code(err));
		if ((err = clEnqueueReadBuffer(app->ocl.cmd_queue, app->kernel_ray_trace.args[3]
				, CL_TRUE, 0, sizeof(cl_uint), (void*)&app->n_hits, 0, NULL, NULL)) != CL_SUCCESS)
			return (error_cl_code(err));
	}
	return (1);
}

void		kernel_ray_trace_destroy(t_app *app)
{
	opencl_kernel_destroy(&app->kernel_ray_trace);
}
