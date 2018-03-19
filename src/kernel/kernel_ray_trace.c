/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernel_ray_trace.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 18:06:33 by paperrin          #+#    #+#             */
/*   Updated: 2018/03/19 17:25:53 by tlernoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				kernel_ray_trace_create(t_app *app)
{
	cl_uint				objs_size;

	if (!opencl_kernel_create_n_args(&app->kernel_ray_trace, &app->ocl, 6))
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
	return (1);
}

int				kernel_ray_trace_launch(t_app *app)
{
	static size_t	old_work_size = 0;
	size_t			ray_hits_size;
	cl_int			err;
	cl_int			hits;

	if (app->n_rays == 0)
		return (1);
	app->kernel_ray_trace.work_size = app->n_rays;
	if (old_work_size < app->n_rays)
	{
		old_work_size = app->n_rays;
		ray_hits_size = app->n_rays - (app->n_rays % app->kernel_prefix_sum.wg_size) + app->kernel_prefix_sum.wg_size;
		opencl_kernel_arg_select_id(&app->kernel_ray_trace, 4);
		opencl_kernel_arg_selected_destroy(&app->kernel_ray_trace);
		if (!opencl_kernel_arg_selected_create(&app->kernel_ray_trace
				, CL_MEM_READ_WRITE
				, sizeof(cl_uint) * ray_hits_size, NULL))
			return (0);
	}
	hits = 0;
	opencl_kernel_arg_select_id(&app->kernel_ray_trace, 5);
		opencl_kernel_arg_selected_destroy(&app->kernel_ray_trace);
		if (!opencl_kernel_arg_selected_create(&app->kernel_ray_trace
				, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR
				, sizeof(cl_int), (void*)&hits))
			return (0);
	opencl_kernel_arg_select_id(&app->kernel_ray_trace, 2);
	if (!opencl_kernel_arg_selected_use_kernel_arg_id(&app->kernel_ray_trace
			, &app->kernel_ray_gen, 2))
		return (0);
	opencl_kernel_arg_select_id(&app->kernel_ray_trace, 3);
	if (!opencl_kernel_arg_selected_use_kernel_arg_id(&app->kernel_ray_trace
			, &app->kernel_ray_gen, 0))
		return (0);
	if (CL_SUCCESS != (err = clEnqueueNDRangeKernel(app->ocl.cmd_queue, app->kernel_ray_trace.kernel
			, 1, NULL, &app->kernel_ray_trace.work_size, NULL, 0, NULL, NULL)))
		return (error_cl_code(err));
	if (CL_SUCCESS != (err = clEnqueueReadBuffer(app->ocl.cmd_queue,
					app->kernel_ray_trace.args[5], CL_TRUE,
					0,
					sizeof(cl_int), (void*)&hits, 0, NULL, NULL)))
		return (error_cl_code(err));
	app->n_hits = (size_t)hits;
	return (1);
}

void		kernel_ray_trace_destroy(t_app *app)
{
	opencl_kernel_destroy(&app->kernel_ray_trace);
}
