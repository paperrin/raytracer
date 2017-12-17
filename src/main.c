/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 16:14:42 by paperrin          #+#    #+#             */
/*   Updated: 2017/12/17 22:59:55 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			app_create(t_app *app)
{
	if (!window_create(&app->win, APP_WIDTH, APP_HEIGHT, APP_TITLE))
		return (0);
	if (!image_create(&app->draw_buf, APP_WIDTH, APP_HEIGHT))
	{
		app_destroy(app, EXIT_FAILURE);
		return (0);
	}
	render(app);
	window_callback_key(&app->win, &callback_key);
	window_loop(&app->win, app);
	return (1);
}

void		app_destroy(t_app *app, int exit_status)
{
	image_destroy(&app->draw_buf);
	window_destroy(&app->win);
	exit(exit_status);
}

int			render(t_app *app)
{
	t_opencl			ocl;
	t_ocl_kernel		kernel_ray_gen;
	cl_int				err;
	const size_t		work_size = APP_WIDTH * APP_HEIGHT;
	t_obj				*obj;
	cl_uint2			screen_size;
	cl_mem				i_cam;
	cl_mem				i_screen_size;
	cl_mem				o_ray_states;
	t_ray_state			*h_ray_states;

	t_ocl_kernel		kernel_ray_trace;
	cl_mem				i_ray_states;
	cl_mem				i_objs;
	cl_mem				i_objs_size;
	cl_mem				o_hits;
	cl_uint				objs_size;
	t_hit				*h_hits;
	size_t				i;

	if (!(h_ray_states = (t_ray_state*)malloc(sizeof(t_ray_state) * work_size)))
		return (catch_error(CL_OUT_OF_HOST_MEMORY));

	if (!(opencl_init(&ocl)))
		return (EXIT_FAILURE);
	opencl_kernel_init(&kernel_ray_gen, &ocl);
	opencl_kernel_create_from_file(&kernel_ray_gen, "./src/cl/kernel_ray_gen_primary.cl", "-I ./include/", 3);

	app->scene.v_obj = ft_vector_create(sizeof(t_obj), NULL, NULL);
	if (!(obj = (t_obj*)ft_vector_push_back(&app->scene.v_obj, NULL)))
		return (catch_error(CL_OUT_OF_HOST_MEMORY));
	*obj = obj_sphere(vec3r(0, 0, 0), 1, 0);
	app->cam.pos = vec3r(0, 0, -3);
	app->cam.dir = vec3r(0, 0, 1);
	app->cam.up = vec3r(0, 1, 0);
	app->cam.right = vec3r(1, 0, 0);

	screen_size.s[0] = APP_WIDTH;
	screen_size.s[1] = APP_HEIGHT;
	i_screen_size = clCreateBuffer(ocl.context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(screen_size), (void*)&screen_size, &err);
	if (err != CL_SUCCESS)
		return (catch_error(err));
	clSetKernelArg(kernel_ray_gen.kernel, 0, sizeof(cl_mem), (void*)&i_screen_size);

	i_cam = clCreateBuffer(ocl.context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(app->cam), (void*)&app->cam, &err);
	if (err != CL_SUCCESS)
		return (catch_error(err));
	clSetKernelArg(kernel_ray_gen.kernel, 1, sizeof(cl_mem), (void*)&i_cam);

	o_ray_states = clCreateBuffer(ocl.context, CL_MEM_WRITE_ONLY, sizeof(t_ray_state) * work_size, NULL, &err);
	if (err != CL_SUCCESS)
		return (catch_error(err));
	clSetKernelArg(kernel_ray_gen.kernel, 2, sizeof(cl_mem), (void*)&o_ray_states);

	clEnqueueNDRangeKernel(ocl.cmd_queue, kernel_ray_gen.kernel, 1, 0, &work_size, 0, 0, 0, 0);
	clEnqueueReadBuffer(ocl.cmd_queue, o_ray_states, CL_TRUE, 0, work_size * sizeof(t_ray_state), h_ray_states, 0, NULL, NULL);



	if (!(h_hits = (t_hit*)malloc(sizeof(t_hit) * work_size)))
		return (catch_error(CL_OUT_OF_HOST_MEMORY));

	opencl_kernel_init(&kernel_ray_trace, &ocl);
	if (!opencl_kernel_create_from_file(&kernel_ray_trace, "./src/cl/kernel_ray_trace.cl", "-I ./include/", 4))
		return (EXIT_FAILURE);

	i_ray_states = clCreateBuffer(ocl.context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(t_ray_state) * work_size, (void*)h_ray_states, &err);
	if (err != CL_SUCCESS)
		return (catch_error(err));
	clSetKernelArg(kernel_ray_trace.kernel, 0, sizeof(cl_mem), (void*)&i_ray_states);

	objs_size = ft_vector_size(&app->scene.v_obj);
	i_objs_size = clCreateBuffer(ocl.context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(cl_uint), (void*)&objs_size, &err);
	if (err != CL_SUCCESS)
		return (catch_error(err));
	clSetKernelArg(kernel_ray_trace.kernel, 2, sizeof(cl_mem), (void*)&i_objs_size);

	i_objs = clCreateBuffer(ocl.context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(t_obj) * objs_size, (void*)app->scene.v_obj.begin, &err);
	if (err != CL_SUCCESS)
		return (catch_error(err));
	clSetKernelArg(kernel_ray_trace.kernel, 1, sizeof(cl_mem), (void*)&i_objs);

	o_hits = clCreateBuffer(ocl.context, CL_MEM_WRITE_ONLY, sizeof(t_hit) * work_size, NULL, &err);
	if (err != CL_SUCCESS)
		return (catch_error(err));
	clSetKernelArg(kernel_ray_trace.kernel, 3, sizeof(cl_mem), (void*)&o_hits);

	clEnqueueNDRangeKernel(ocl.cmd_queue, kernel_ray_trace.kernel, 1, 0, &work_size, 0, 0, 0, 0);
	clEnqueueReadBuffer(ocl.cmd_queue, o_hits, CL_TRUE, 0, work_size * sizeof(t_hit), h_hits, 0, NULL, NULL);

	i = -1;
	while (++i < work_size)
	{
		if (h_hits[i].t >= 0)
		{
			image_set_pixel(&app->draw_buf, i % APP_WIDTH, i / APP_WIDTH, ft_clrf_rgb(1, 0, 0));
		}
		else
			image_set_pixel(&app->draw_buf, i % APP_WIDTH, i / APP_WIDTH, ft_clrf_rgb(0, 0, 0));
	}

	window_clear(&app->win, ft_clrf_rgb(0, 0, 0));
	image_put(&app->draw_buf, 0, 0);
	window_swap_buffers(&app->win);
	opencl_release_all(&ocl);

	return (1);
}
#include <stdio.h>
#include "ft_printf.h"

int			main(int ac, char **av)
{
	t_app				app;

	(void)ac;
	(void)av;
	if (!app_create(&app))
		return (EXIT_FAILURE);
	app_destroy(&app, EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
