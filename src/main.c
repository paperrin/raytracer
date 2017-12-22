/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 16:14:42 by paperrin          #+#    #+#             */
/*   Updated: 2017/12/22 18:30:38 by paperrin         ###   ########.fr       */
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
	if (!render(app))
		app_destroy(app, EXIT_FAILURE);
	window_callback_key(&app->win, &callback_key);
	window_loop(&app->win, app);
	return (1);
}

void		app_destroy(t_app *app, int exit_status)
{
	kernel_ray_gen_primary_destroy(app);
	kernel_ray_trace_destroy(app);
	opencl_destroy(&app->ocl);
	image_destroy(&app->draw_buf);
	window_destroy(&app->win);
	exit(exit_status);
}

int			render(t_app *app)
{
	if (!kernel_ray_gen_primary_launch(app))
		return (0);
	if (!kernel_ray_trace_launch(app))
		return (0);
	window_clear(&app->win, ft_clrf_rgb(0, 0, 0));
	image_put(&app->draw_buf, 0, 0);
	window_swap_buffers(&app->win);
	return (1);
}

int			main(int ac, char **av)
{
	t_app				app;
	t_obj				*obj;

	app.scene.v_obj = ft_vector_create(sizeof(t_obj), NULL, NULL);
	if (!(obj = (t_obj*)ft_vector_push_back(&app.scene.v_obj, NULL)))
		return (error_cl_code(CL_OUT_OF_HOST_MEMORY));
	*obj = obj_sphere(vec3r(0, 0, 0), 1, 0);
	app.cam.pos = vec3r(0, 0, -2.5);
	app.cam.dir = vec3r(0, 0, 1);
	app.cam.up = vec3r(0, 1, 0);
	app.cam.right = vec3r(1, 0, 0);

	(void)ac;
	(void)av;
	if (!app_create(&app))
		return (EXIT_FAILURE);
	app_destroy(&app, EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
