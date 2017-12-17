/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 16:14:42 by paperrin          #+#    #+#             */
/*   Updated: 2017/12/17 19:30:54 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			app_create(t_app *app)
{
	if (!window_create(&app->win, APP_WIDTH, APP_HEIGHT, APP_TITLE))
		return (0);
	render(&app->scene, &app->cam);
	window_callback_key(&app->win, &callback_key);
	window_loop(&app->win, app);
	return (1);
}

void		app_destroy(t_app *app, int exit_status)
{
	window_destroy(&app->win);
	exit(exit_status);
}

int			render(t_scene *scene, t_camera *cam)
{
	(void)scene;
	(void)cam;
	return (1);
}
#include <stdio.h>

int			main(int ac, char **av)
{
	t_app				app;
	t_opencl			ocl;
	t_ocl_kernel		kernel;
	cl_int						err;
	const size_t				work_size = APP_WIDTH * APP_HEIGHT;
	t_obj						*obj;
	cl_uint2		screen_size;
	cl_mem			i_cam;
	cl_mem			i_screen_size;
	cl_mem			o_ray_states;
	t_ray_state		*h_ray_states;
	int				id;

	(void)ac;
	(void)av;

	if (!(h_ray_states = (t_ray_state*)malloc(sizeof(t_ray_state) * APP_WIDTH * APP_HEIGHT)))
		return (EXIT_FAILURE);

	if (!(opencl_init(&ocl)))
		return (EXIT_FAILURE);
	opencl_kernel_init(&kernel, &ocl);
	opencl_kernel_create_from_file(&kernel, "./src/cl/kernel_ray_gen_primary.cl", "-I ./include/", 3);

	app.scene.v_obj = ft_vector_create(sizeof(t_obj), NULL, NULL);
	if (!(obj = (t_obj*)ft_vector_push_back(&app.scene.v_obj, NULL)))
		return (catch_error(CL_OUT_OF_HOST_MEMORY));
	*obj = obj_sphere(vec3r(0, 0, 0), 0.5, 0);
	app.cam.pos = vec3r(0, 0, -3);
	app.cam.dir = vec3r(0, 0, 1);
	app.cam.up = vec3r(0, 1, 0);
	app.cam.right = vec3r(1, 0, 0);

	screen_size.s[0] = APP_WIDTH;
	screen_size.s[1] = APP_HEIGHT;
	i_screen_size = clCreateBuffer(ocl.context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(screen_size), (void*)&screen_size, &err);
	if (err != CL_SUCCESS)
		return (catch_error(err));
	clSetKernelArg(kernel.kernel, 0, sizeof(cl_mem), (void*)&i_screen_size);

	i_cam = clCreateBuffer(ocl.context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(app.cam), (void*)&app.cam, &err);
	if (err != CL_SUCCESS)
		return (catch_error(err));
	clSetKernelArg(kernel.kernel, 1, sizeof(cl_mem), (void*)&i_cam);

/*
	kernel_arg_set(kernel, kernel_arg_dup(ocl, flags, size, src), id);
*/

	o_ray_states = clCreateBuffer(ocl.context, CL_MEM_WRITE_ONLY, sizeof(t_ray_state) * work_size, NULL, &err);
	if (err != CL_SUCCESS)
		return (catch_error(err));
	clSetKernelArg(kernel.kernel, 2, sizeof(cl_mem), (void*)&o_ray_states);

	clEnqueueNDRangeKernel(ocl.cmd_queue, kernel.kernel, 1, 0, &work_size, 0, 0, 0, 0);
	clEnqueueReadBuffer(ocl.cmd_queue, o_ray_states, CL_TRUE, 0, work_size * sizeof(t_ray_state), h_ray_states, 0, NULL, NULL);


	id = 0;
	printf("%f\n", h_ray_states[id].ray.dir.s[0]);
	printf("%f\n", h_ray_states[id].ray.dir.s[1]);
	printf("%f\n", h_ray_states[id].ray.dir.s[2]);

	id = APP_WIDTH * APP_HEIGHT - 1;
	printf("%f\n", h_ray_states[id].ray.dir.s[0]);
	printf("%f\n", h_ray_states[id].ray.dir.s[1]);
	printf("%f\n", h_ray_states[id].ray.dir.s[2]);

	opencl_release_all(&ocl);

	if (!app_create(&app))
		return (EXIT_FAILURE);
	app_destroy(&app, EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
