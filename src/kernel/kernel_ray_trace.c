/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernel_ray_trace.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 18:06:33 by paperrin          #+#    #+#             */
/*   Updated: 2017/12/22 18:29:31 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				kernel_ray_trace_create(t_app *app)
{
	cl_uint				objs_size;

	if (!(app->hits = (t_hit*)malloc(sizeof(t_hit) * APP_WIDTH * APP_HEIGHT)))
		return (error_cl_code(CL_OUT_OF_HOST_MEMORY));
	app->kernel_ray_trace.work_size = APP_WIDTH * APP_HEIGHT;
	if (!opencl_kernel_create_n_args(&app->kernel_ray_trace, &app->ocl, 4))
		return (0);
	if (!opencl_kernel_load_from_file(&app->kernel_ray_trace
				, "./src/cl/kernel_ray_trace.cl", "-I ./include/"))
		return (0);
	opencl_kernel_arg_select_id(&app->kernel_ray_trace, 0);
	opencl_kernel_arg_selected_use_kernel_arg_id(&app->kernel_ray_trace
			, &app->kernel_ray_gen, 2);
	objs_size = ft_vector_size(&app->scene.v_obj);
	opencl_kernel_arg_select_id(&app->kernel_ray_trace, 1);
	if (!opencl_kernel_arg_selected_create(&app->kernel_ray_trace
			, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR
			, sizeof(t_obj) * objs_size, (void*)app->scene.v_obj.begin))
		return (0);
	opencl_kernel_arg_select_id(&app->kernel_ray_trace, 2);
	if (!opencl_kernel_arg_selected_create(&app->kernel_ray_trace
			, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR
			, sizeof(cl_uint), (void*)&objs_size))
		return (0);
	opencl_kernel_arg_select_id(&app->kernel_ray_trace, 3);
	if (!opencl_kernel_arg_selected_create(&app->kernel_ray_trace
			, CL_MEM_WRITE_ONLY
			, sizeof(t_hit) * app->kernel_ray_trace.work_size, NULL))
		return (0);
	return (1);
}

int				kernel_ray_trace_launch(t_app *app)
{
	size_t		work_size;
	size_t		i;

	work_size = app->kernel_ray_trace.work_size;
	clEnqueueNDRangeKernel(app->ocl.cmd_queue, app->kernel_ray_trace.kernel
			, 1, 0, &work_size, 0, 0, 0, 0);
	clEnqueueReadBuffer(app->ocl.cmd_queue, app->kernel_ray_trace.args[3]
			, CL_TRUE, 0, work_size * sizeof(t_hit), app->hits, 0, NULL, NULL);
	i = -1;
	while (++i < work_size)
	{
		if (app->hits[i].t >= 0)
			image_set_pixel(&app->draw_buf, i % APP_WIDTH, i / APP_WIDTH
					, ft_clrf_rgb(1, 0, 0));
		else
			image_set_pixel(&app->draw_buf, i % APP_WIDTH, i / APP_WIDTH
					, ft_clrf_rgb(0, 0, 0));
	}
	return (1);
}

void		kernel_ray_trace_destroy(t_app *app)
{
	opencl_kernel_destroy(&app->kernel_ray_trace);
	free(app->hits);
}
