/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 16:14:42 by paperrin          #+#    #+#             */
/*   Updated: 2018/03/23 22:19:43 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "ppm.h"

#include "scene_parser.h"

int			app_create(t_app *app)
{
	t_ast *ast;
	/*
	t_token_stream		*tkstream;
	t_token			*tk;

	if ((tkstream = tkstream_open("example.rt")))
	{
		while (1)
		{
			if ((tk = tkstream_next(tkstream)))
				tkstream_print_token(tk);
			else
				return (0);
		}
	}
	else
		return (0);*/
	if ((ast = ast_parse("example.rt")))
	{
		ast_destroy(&ast);
		return (1);
	}
	else
		return (0);
	if (!window_create(&app->win, 720, 480, APP_TITLE))
		return (0);
	if (!image_create(&app->draw_buf, app->win.width, app->win.height))
		app_destroy(app, EXIT_FAILURE);
	if (!(opencl_create(&app->ocl, 1)))
		app_destroy(app, EXIT_FAILURE);
	if (!kernel_ray_gen_primary_create(app))
		app_destroy(app, EXIT_FAILURE);
	if (!kernel_ray_trace_create(app))
		app_destroy(app, EXIT_FAILURE);
	if (!kernel_clear_create(app))
		app_destroy(app, EXIT_FAILURE);
	if (!kernel_ray_shade_create(app))
		app_destroy(app, EXIT_FAILURE);
	window_callback_key(&app->win, &callback_key);
	window_callback_mouse_motion(&app->win, &callback_mouse_motion);
	glfwSetInputMode(app->win.glfw_win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	app->mouse_captured = 1;
	window_callback_loop(&app->win, &render, app);
	return (1);
}

void		app_destroy(t_app *app, int exit_status)
{
	kernel_ray_gen_primary_destroy(app);
	kernel_ray_trace_destroy(app);
	kernel_clear_destroy(app);
	kernel_ray_shade_destroy(app);
	opencl_destroy(&app->ocl);
	image_destroy(&app->draw_buf);
	window_destroy(&app->win);
	exit(exit_status);
}

void		render(void *user_ptr, double elapsed)
{
	static double			last_time = -1;
	static unsigned long	hits_per_sec = 0;
	static unsigned long	rays_per_sec = 0;
	static size_t			n_frames = 0;
	t_app					*app;
	int						depth;

	app = (t_app*)user_ptr;
	process_input(app, (last_time < 0) ? 0 : elapsed);
	camera_update(&app->cam);
	if (!kernel_ray_gen_primary_launch(app))
		app_destroy(app, EXIT_FAILURE);
	if (!kernel_clear_launch(app))
		app_destroy(app, EXIT_FAILURE);
	depth = -1;
	while (++depth <= 1)
	{
		if (!kernel_ray_trace_launch(app))
			app_destroy(app, EXIT_FAILURE);
		hits_per_sec += app->n_hits;
		rays_per_sec += app->n_rays;
		if (!kernel_ray_shade_launch(app))
			app_destroy(app, EXIT_FAILURE);
	}
	clFinish(app->ocl.cmd_queue);
	clEnqueueReadBuffer(app->ocl.cmd_queue, app->kernel_clear.args[0]
			, CL_TRUE, 0, sizeof(cl_float) * 4 * app->win.width * app->win.height
			, app->draw_buf.pixels, 0, 0, 0);
	image_put(&app->draw_buf, 0, 0);
	window_swap_buffers(&app->win);
	n_frames++;
	if (glfwGetTime() - last_time > 1)
	{
		last_time = glfwGetTime();
		printf("FPS: %4lu   |   Rays: %10u   |   Rays/ms: %10lu    |    Secondary: %10lu\n", n_frames, app->n_hits, hits_per_sec / 1000, rays_per_sec / 1000);
		n_frames = 0;
		hits_per_sec = 0;
		rays_per_sec = 0;
	}
}

int			main(int ac, char **av)
{
	t_app				app;
	t_obj				*obj;
	t_light				*light;
	t_material			*mat;
	t_texture			*texture;
	char			*pixels;
	size_t			width;
	size_t			height;
	size_t			max;

	app.scene.v_obj = ft_vector_create(sizeof(t_obj), NULL, NULL);
/*
	if (!(obj = (t_obj*)ft_vector_push_back(&app.scene.v_obj, NULL)))
		return (error_cl_code(CL_OUT_OF_HOST_MEMORY));
	*obj = obj_sphere(vec3r(0, -10000, 0), 10000, 3);

	if (!(obj = (t_obj*)ft_vector_push_back(&app.scene.v_obj, NULL)))
		return (error_cl_code(CL_OUT_OF_HOST_MEMORY));
	*obj = obj_sphere(vec3r(-10000.1, 0, 0), 10000, 4);

	if (!(obj = (t_obj*)ft_vector_push_back(&app.scene.v_obj, NULL)))
		return (error_cl_code(CL_OUT_OF_HOST_MEMORY));
	*obj = obj_sphere(vec3r(10002, 0, 0), 10000, 4);

	if (!(obj = (t_obj*)ft_vector_push_back(&app.scene.v_obj, NULL)))
		return (error_cl_code(CL_OUT_OF_HOST_MEMORY));
	*obj = obj_sphere(vec3r(0, 0, 10000), 10000, 4);

	if (!(obj = (t_obj*)ft_vector_push_back(&app.scene.v_obj, NULL)))
		return (error_cl_code(CL_OUT_OF_HOST_MEMORY));
	*obj = obj_sphere(vec3r(0, 0.02, -2), 0.02, 0);

	if (!(obj = (t_obj*)ft_vector_push_back(&app.scene.v_obj, NULL)))
		return (error_cl_code(CL_OUT_OF_HOST_MEMORY));
	*obj = obj_plane(vec3r(0, 1, 0), vec3r(0, 1, 0), 0);
	if (!(obj = (t_obj*)ft_vector_push_back(&app.scene.v_obj, NULL)))
		return (error_cl_code(CL_OUT_OF_HOST_MEMORY));
	*obj = obj_sphere(vec3r(0.3, 0.1, -0.3), 0.1, 1);
*/
	if (!(obj = (t_obj*)ft_vector_push_back(&app.scene.v_obj, NULL)))
		return (error_cl_code(CL_OUT_OF_HOST_MEMORY));
	*obj = obj_sphere(vec3r(-0.6, 0.5, -0.7), 0.5, 0);
/*
	if (!(obj = (t_obj*)ft_vector_push_back(&app.scene.v_obj, NULL)))
		return (error_cl_code(CL_OUT_OF_HOST_MEMORY));
	*obj = obj_sphere(vec3r(0.6, 0.5, 0), 0.5, 1);
*/
	if (!(obj = (t_obj*)ft_vector_push_back(&app.scene.v_obj, NULL)))
		return (error_cl_code(CL_OUT_OF_HOST_MEMORY));
	*obj = obj_plane(vec3r(0, 0, 1), vec3r(0, 0, -1), vec3r(1, 0, 0), 1);
	if (!(obj = (t_obj*)ft_vector_push_back(&app.scene.v_obj, NULL)))
		return (error_cl_code(CL_OUT_OF_HOST_MEMORY));
	*obj = obj_plane(vec3r(0, 0, -3), vec3r(0, 0, 1), vec3r(1, 0, 0), 1);

/*
	if (!(obj = (t_obj*)ft_vector_push_back(&app.scene.v_obj, NULL)))
		return (error_cl_code(CL_OUT_OF_HOST_MEMORY));
	*obj = obj_plane(vec3r(0, 0, 1), vec3r(0, 0, -1), vec3r(0, 0, 1), 3);

	if (!(obj = (t_obj*)ft_vector_push_back(&app.scene.v_obj, NULL)))
		return (error_cl_code(CL_OUT_OF_HOST_MEMORY));
	*obj = obj_plane(vec3r(1, 0, 0), vec3r(-1, 0, 0), vec3r(0, 1, 0), 4);
*/
/*
	if (!(obj = (t_obj*)ft_vector_push_back(&app.scene.v_obj, NULL)))
		return (error_cl_code(CL_OUT_OF_HOST_MEMORY));
	*obj = obj_sphere(vec3r(0, -100000, 0), 100000, 3);
*/
	app.scene.v_material = ft_vector_create(sizeof(t_material), NULL, NULL);
	if (!(mat = (t_material*)ft_vector_push_back(&app.scene.v_material, NULL)))
		return (error_cl_code(CL_OUT_OF_HOST_MEMORY));
	mat->color = vec3f(1, 1, 1);
	mat->reflection = 0;
	mat->refraction = 0;
	mat->texture_id = 0;
	if (!(mat = (t_material*)ft_vector_push_back(&app.scene.v_material, NULL)))
		return (error_cl_code(CL_OUT_OF_HOST_MEMORY));
	mat->color = vec3f(1, 1, 1);
	mat->reflection = 0.8;
	mat->refraction = 0;
	mat->texture_id = -1;
	if (!(mat = (t_material*)ft_vector_push_back(&app.scene.v_material, NULL)))
		return (error_cl_code(CL_OUT_OF_HOST_MEMORY));
	mat->color = vec3f(0.6, 0.6, 1);
	mat->reflection = 0;
	mat->refraction = 0;
	mat->texture_id = -1;
	if (!(mat = (t_material*)ft_vector_push_back(&app.scene.v_material, NULL)))
		return (error_cl_code(CL_OUT_OF_HOST_MEMORY));
	mat->color = vec3f(0.3, 1, 0.3);
	mat->reflection = 0;
	mat->refraction = 0;
	mat->texture_id = -1;
	if (!(mat = (t_material*)ft_vector_push_back(&app.scene.v_material, NULL)))
		return (error_cl_code(CL_OUT_OF_HOST_MEMORY));
	mat->color = vec3f(1, 0.3, 0.3);
	mat->reflection = 0.8;
	mat->refraction = 0;
	mat->texture_id = -1;

	app.scene.v_texture = ft_vector_create(sizeof(t_texture), NULL, NULL);
	if (!(pixels = ft_ppm_get("textures/test.ppm", &width, &height, &max)))
		return (0);
	if (!(texture = (t_texture*)ft_vector_push_back(&app.scene.v_texture, NULL)))
		return (error_cl_code(CL_OUT_OF_HOST_MEMORY));
	printf("texture_size: %lu, %lu, %lu\n", width, height, max);
	app.scene.texture_pixels = (cl_uchar*)pixels;
	app.scene.n_texture_pixels = width * height;
	texture->pixels_offset = 0;
	texture->width = width;
	texture->height = height;
	texture->filter = e_filter_nearest;
	if (!(texture = (t_texture*)ft_vector_push_back(&app.scene.v_texture, NULL)))
		return (error_cl_code(CL_OUT_OF_HOST_MEMORY));
	texture->pixels_offset = 0;
	texture->width = width;
	texture->height = height;
	texture->filter = e_filter_nearest;

	app.config.ambient = vec3f(1, 1, 1);
	app.config.samples_width = 1;
	app.scene.v_light = ft_vector_create(sizeof(t_light), NULL, NULL);
	if (!(light = (t_light*)ft_vector_push_back(&app.scene.v_light, NULL)))
		return (error_cl_code(CL_OUT_OF_HOST_MEMORY));
	light->type = light_type_point;
	light->color = vec3f(1, 0.8, 0.7);
	light->intensity = 20;
	light->as.point.pos = vec3r(0.9, 1, -1);
	if (!(light = (t_light*)ft_vector_push_back(&app.scene.v_light, NULL)))
		return (error_cl_code(CL_OUT_OF_HOST_MEMORY));
	light->type = light_type_point;
	light->color = vec3f(1, 0.8, 0.7);
	light->intensity = 20;
	light->as.point.pos = vec3r(-0.5, 0.8, 0.9);

	app.cam.cam_data.pos = vec3r(0, 0.5, -2);
	(void)ac;
	(void)av;

	if (!app_create(&app))
		return (EXIT_FAILURE);
	app_destroy(&app, EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
