/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernel_ray_sort.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlernoul <tlernoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 16:36:28 by tlernoul          #+#    #+#             */
/*   Updated: 2018/03/21 17:09:06 by tlernoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int				kernel_ray_sort_create(t_app *app)
{
	cl_int			err;

	if (!opencl_kernel_create_n_args(&app->kernel_ray_sort, &app->ocl, 5))
		return (0);
	if (!opencl_kernel_load_from_file(&app->kernel_ray_sort
				, "./src/cl/kernel_ray_sort.cl", "-I ./include/"))
		return (0);
	if (CL_SUCCESS != (err = clGetKernelWorkGroupInfo(
			app->kernel_ray_sort.kernel, app->ocl.device,
			CL_KERNEL_PREFERRED_WORK_GROUP_SIZE_MULTIPLE,
			sizeof(app->kernel_ray_sort.wg_size),
			(void*)&app->kernel_ray_sort.wg_size, NULL)))
		return (error_cl_code(err));
	if (CL_SUCCESS != (err = clSetKernelArg(app->kernel_ray_sort.kernel, 3, sizeof(t_ray_state) * app->kernel_ray_sort.wg_size, NULL)))
		return (error_cl_code(err));
	if (CL_SUCCESS != (err = clSetKernelArg(app->kernel_ray_sort.kernel, 4, sizeof(t_ray_state) * app->kernel_ray_sort.wg_size, NULL)))
		return (error_cl_code(err));
	return (1);
}

int				kernel_ray_sort_launch(t_app *app)
{
	cl_uint			new_app_n_rays;
	cl_int			err;
	cl_uint			n_rays;

	n_rays = (cl_uint)app->n_rays;
	opencl_kernel_arg_select_id(&app->kernel_ray_sort, 2);
	opencl_kernel_arg_selected_destroy(&app->kernel_ray_sort);
	if (!opencl_kernel_arg_selected_create(&app->kernel_ray_sort,
				CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
		sizeof(cl_uint), (void*)&n_rays))
		return (0);
	if (!app->n_rays || !app->should_sort_rays)
		return (1);
	app->kernel_ray_sort.work_size = app->kernel_ray_sort.wg_size;
		opencl_kernel_arg_select_id(&app->kernel_ray_sort, 0);
	if (!opencl_kernel_arg_selected_use_kernel_arg_id(&app->kernel_ray_sort
				, &app->kernel_ray_trace, 4))
		return (0);
	opencl_kernel_arg_select_id(&app->kernel_ray_sort, 1);
	if (!opencl_kernel_arg_selected_use_kernel_arg_id(&app->kernel_ray_sort
				, &app->kernel_ray_gen, 2))
		return (0);
	if (CL_SUCCESS != (err = clEnqueueNDRangeKernel(app->ocl.cmd_queue, app->kernel_ray_sort.kernel
			, 1, NULL, &app->kernel_ray_sort.work_size, &app->kernel_ray_sort.wg_size, 0, NULL, NULL)))
		return (error_cl_code(err));
	if (CL_SUCCESS != (err = clEnqueueReadBuffer(app->ocl.cmd_queue,
					app->kernel_ray_trace.args[4], CL_TRUE,
					sizeof(cl_uint) * (app->n_rays - 1),
					sizeof(cl_uint), (void*)&new_app_n_rays, 0, NULL, NULL)))
		return (error_cl_code(err));
/*	printf("appn %u (diff) %d | \nrays %u | hits %u\n",new_app_n_rays,(int)new_app_n_rays - (int)app->n_hits , app->n_rays, app->n_hits);
*/	
	n_rays = (cl_uint)app->n_hits;
	opencl_kernel_arg_select_id(&app->kernel_ray_sort, 2);
	opencl_kernel_arg_selected_destroy(&app->kernel_ray_sort);
	if (!opencl_kernel_arg_selected_create(&app->kernel_ray_sort,
	CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(cl_uint), (void*)&n_rays))
		return (0);
	return (1);
}

void			kernel_ray_sort_destroy(t_app *app)
{
	opencl_kernel_destroy(&app->kernel_ray_sort);
}
