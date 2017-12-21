/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernel_ray_gen_primary.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 21:50:02 by paperrin          #+#    #+#             */
/*   Updated: 2017/12/18 21:53:18 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			kernel_ray_gen_primary_init(t_app *app)
{
	if (!(h_ray_states = (t_ray_state*)malloc(sizeof(t_ray_state) * work_size)))
		return (catch_error(CL_OUT_OF_HOST_MEMORY));
	opencl_kernel_set_ocl_nb_args(&app->kernel_ray_gen, &ocl, 3);
	if (!opencl_kernel_load_from_file(&app->kernel_ray_gen, "./src/cl/kernel_ray_gen_primary.cl", "-I ./include/"))
		return (EXIT_FAILURE);
	screen_size.s[0] = APP_WIDTH;
	screen_size.s[1] = APP_HEIGHT;
	i_screen_size = clCreateBuffer(ocl.context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(screen_size), (void*)&screen_size, &err);
	if (err != CL_SUCCESS)
		return (catch_error(err));
	clSetKernelArg(app->kernel_ray_gen.kernel, 0, sizeof(cl_mem), (void*)&i_screen_size);

	i_cam = clCreateBuffer(ocl.context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(app->cam), (void*)&app->cam, &err);
	if (err != CL_SUCCESS)
		return (catch_error(err));
	clSetKernelArg(app->kernel_ray_gen.kernel, 1, sizeof(cl_mem), (void*)&i_cam);

	o_ray_states = clCreateBuffer(ocl.context, CL_MEM_WRITE_ONLY, sizeof(t_ray_state) * work_size, NULL, &err);
	if (err != CL_SUCCESS)
		return (catch_error(err));
	clSetKernelArg(app->kernel_ray_gen.kernel, 2, sizeof(cl_mem), (void*)&o_ray_states);

	clEnqueueNDRangeKernel(ocl.cmd_queue, app->kernel_ray_gen.kernel, 1, 0, &work_size, 0, 0, 0, 0);
	clEnqueueReadBuffer(ocl.cmd_queue, o_ray_states, CL_TRUE, 0, work_size * sizeof(t_ray_state), h_ray_states, 0, NULL, NULL);



}

int			kernel_ray_gen_primary_launch(t_app *app)
{
}
