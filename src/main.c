/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 16:14:42 by paperrin          #+#    #+#             */
/*   Updated: 2018/01/15 01:59:34 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			app_create(t_app *app)
{
	if (!window_create(&app->win, APP_WIDTH, APP_HEIGHT, APP_TITLE))
		return (0);
	if (!image_create(&app->draw_buf, APP_WIDTH, APP_HEIGHT))
		app_destroy(app, EXIT_FAILURE);
	if (!(opencl_create(&app->ocl)))
		app_destroy(app, EXIT_FAILURE);
	if (!kernel_ray_gen_primary_create(app))
		app_destroy(app, EXIT_FAILURE);
	if (!kernel_ray_trace_create(app))
		app_destroy(app, EXIT_FAILURE);
	if (!kernel_compute_texels_create(app))
		app_destroy(app, EXIT_FAILURE);
	if (!kernel_combine_texels_create(app))
		app_destroy(app, EXIT_FAILURE);
	window_callback_key(&app->win, &callback_key);
	window_callback_loop(&app->win, &render, app);
	return (1);
}

void		app_destroy(t_app *app, int exit_status)
{
	kernel_ray_gen_primary_destroy(app);
	kernel_ray_trace_destroy(app);
	kernel_compute_texels_destroy(app);
	kernel_combine_texels_destroy(app);
	opencl_destroy(&app->ocl);
	image_destroy(&app->draw_buf);
	window_destroy(&app->win);
	exit(exit_status);
}

void		render(void *user_ptr)
{
	static double		last_time = -1;
	static size_t		n_frames = 0;
	t_app				*app;

	if (last_time < 0)
		last_time = glfwGetTime();
	app = (t_app*)user_ptr;
	if (!kernel_ray_gen_primary_launch(app))
		app_destroy(app, EXIT_FAILURE);
	if (!kernel_ray_trace_launch(app))
		app_destroy(app, EXIT_FAILURE);
	if (!kernel_compute_texels_launch(app))
		app_destroy(app, EXIT_FAILURE);
	if (!kernel_combine_texels_launch(app))
		app_destroy(app, EXIT_FAILURE);
	window_clear(&app->win, ft_clrf_rgb(0, 0, 0));
	image_put(&app->draw_buf, 0, 0);
	window_swap_buffers(&app->win);
	n_frames++;
	if (glfwGetTime() - last_time > 1)
	{
		last_time = glfwGetTime();
		ft_printf("FPS: %lu\n", n_frames);
		n_frames = 0;
	}
}

int			main(int ac, char **av)
{
	t_app				app;
	t_obj				*obj;
	t_light				*light;

	app.scene.v_obj = ft_vector_create(sizeof(t_obj), NULL, NULL);
	if (!(obj = (t_obj*)ft_vector_push_back(&app.scene.v_obj, NULL)))
		return (error_cl_code(CL_OUT_OF_HOST_MEMORY));
	*obj = obj_sphere(vec3r(0, 0, 0), 1, 0);
	if (!(obj = (t_obj*)ft_vector_push_back(&app.scene.v_obj, NULL)))
		return (error_cl_code(CL_OUT_OF_HOST_MEMORY));
	*obj = obj_sphere(vec3r(1.7, 0.5, 0), 0.5, 0);
	if (!(obj = (t_obj*)ft_vector_push_back(&app.scene.v_obj, NULL)))
		return (error_cl_code(CL_OUT_OF_HOST_MEMORY));
	*obj = obj_sphere(vec3r(-1.5, -0.5, 0), 0.3, 0);
	app.cam.pos = vec3r(0, 0, -2.5);
	app.cam.dir = vec3r(0, 0, 1);
	app.cam.up = vec3r(0, 1, 0);
	app.cam.right = vec3r(1, 0, 0);

	app.scene.v_light = ft_vector_create(sizeof(t_light), NULL, NULL);
	if (!(light = (t_light*)ft_vector_push_back(&app.scene.v_light, NULL)))
		return (error_cl_code(CL_OUT_OF_HOST_MEMORY));
	(void)ac;
	(void)av;
	if (!app_create(&app))
		return (EXIT_FAILURE);
	app_destroy(&app, EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
