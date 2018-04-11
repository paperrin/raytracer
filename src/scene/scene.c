/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 20:58:15 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/11 22:57:32 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "ppm.h"

int		scene_create(t_scene *const scene)
{
	scene->v_obj = ft_vector_create(sizeof(t_obj), NULL, NULL);
	scene->v_material = ft_vector_create(sizeof(t_material), NULL, NULL);
	scene->v_texture = ft_vector_create(sizeof(t_texture), NULL, NULL);
	scene->v_light = ft_vector_create(sizeof(t_light), NULL, NULL);
	ft_matrix_to_identity(&scene->mx);
	return (1);
}

void	scene_destroy(t_scene *const scene)
{
	ft_vector_destroy(&scene->v_obj);
	ft_vector_destroy(&scene->v_material);
	ft_vector_destroy(&scene->v_texture);
	ft_vector_destroy(&scene->v_light);
}

void	scene_transform_real3(t_scene *const scene, t_real3 vec3r)
{
	t_vec3f		vec3f;

	vec3f.x = (float)vec3r.s[0];
	vec3f.y = (float)vec3r.s[1];
	vec3f.z = (float)vec3r.s[2];
	vec3f = ft_vec3f_transform(&vec3f, *scene->mx);
	vec3r.s[0] = (t_real)vec3f.x;
	vec3r.s[1] = (t_real)vec3f.y;
	vec3r.s[2] = (t_real)vec3f.z;
}

int		scene_load(t_scene *const scene, t_app *const app)
{
	t_light				*light;
	t_material			*mat;
	t_texture			*texture;
	unsigned char		*pixels;
	size_t				width;
	size_t				height;
	unsigned int		max_val;


	app->config.screen_size.s[0] = APP_WIDTH;
	app->config.screen_size.s[1] = APP_HEIGHT;
	app->config.color_epsilon = 1.f / 255;
	app->config.intersection_bias = 1e-3;
	app->config.z_far = 20000;

	app->config.ambient_c = vec3f(1, 1, 1);
	app->config.ambient_i = 0.05;
	app->config.camera_light_c = vec3f(1, 1, 1);
	app->config.camera_light_i = 0.05;
	app->config.samples_width = 1;
	app->config.max_depth = 0;
	app->config.projection_depth = 0;
	app->config.post_filters = e_post_filter_none;

	if (!(pixels = ft_ppm_file_read("textures/max_val.ppm", &width, &height, &max_val)))
		return (error_string("Could not read ppm file"));
	if (!(texture = (t_texture*)ft_vector_push_back(&scene->v_texture, NULL)))
		return (error_cl_code(CL_OUT_OF_HOST_MEMORY));
	scene->texture_pixels = (cl_uchar*)pixels;
	scene->n_texture_pixels = width * height * (max_val <= 255 ? 1 : 2);
	texture->pixels_offset = 0;
	texture->width = width;
	texture->height = height;
	texture->max_val = max_val;
	texture->filter = e_filter_nearest;

	if (!(mat = (t_material*)ft_vector_push_back(&scene->v_material, NULL)))
		return (error_cl_code(CL_OUT_OF_HOST_MEMORY));
	mat->color = vec3f(1, 1, 1);
	mat->reflection = 0;
	mat->refraction = 0;
	mat->texture_id = 0;
	if (!(light = (t_light*)ft_vector_push_back(&scene->v_light, NULL)))
		return (error_cl_code(CL_OUT_OF_HOST_MEMORY));
	light->type = e_light_type_point;
	light->color = vec3f(1, 1, 1);
	light->intensity = 200;
	light->as.point.pos = vec3r(3, 3, -3);

	app->cam.cam_data.pos = vec3r(0, 0, -1);

	if (!scene_add_sphere(scene))
		return (0);
	return (1);
	/*
	t_obj				*obj;
	t_light				*light;
	t_material			*mat;
	float				offset;

	offset = 0.51;

	if (!(obj = (t_obj*)ft_vector_push_back(&scene->v_obj, NULL)))
		return (error_cl_code(CL_OUT_OF_HOST_MEMORY));
	*obj = obj_aligned_cube(vec3r(-offset, -offset, offset), vec3r(1, 1, 1), 7);
	if (!(obj = (t_obj*)ft_vector_push_back(&scene->v_obj, NULL)))
		return (error_cl_code(CL_OUT_OF_HOST_MEMORY));
	*obj = obj_aligned_cube(vec3r(offset, -offset, offset), vec3r(1, 1, 1), 7);
	if (!(obj = (t_obj*)ft_vector_push_back(&scene->v_obj, NULL)))
		return (error_cl_code(CL_OUT_OF_HOST_MEMORY));
	*obj = obj_aligned_cube(vec3r(-offset, offset, offset), vec3r(1, 1, 1), 7);
	if (!(obj = (t_obj*)ft_vector_push_back(&scene->v_obj, NULL)))
		return (error_cl_code(CL_OUT_OF_HOST_MEMORY));
	*obj = obj_aligned_cube(vec3r(offset, offset, offset), vec3r(1, 1, 1), 7);
	if (!(obj = (t_obj*)ft_vector_push_back(&scene->v_obj, NULL)))
		return (error_cl_code(CL_OUT_OF_HOST_MEMORY));
	*obj = obj_aligned_cube(vec3r(-offset, -offset, -offset), vec3r(1, 1, 1), 7);
	if (!(obj = (t_obj*)ft_vector_push_back(&scene->v_obj, NULL)))
		return (error_cl_code(CL_OUT_OF_HOST_MEMORY));
	*obj = obj_aligned_cube(vec3r(offset, -offset, -offset), vec3r(1, 1, 1), 7);
	if (!(obj = (t_obj*)ft_vector_push_back(&scene->v_obj, NULL)))
		return (error_cl_code(CL_OUT_OF_HOST_MEMORY));
	*obj = obj_aligned_cube(vec3r(-offset, offset, -offset), vec3r(1, 1, 1), 7);




	if (!(obj = (t_obj*)ft_vector_push_back(&scene->v_obj, NULL)))
		return (error_cl_code(CL_OUT_OF_HOST_MEMORY));
	*obj = obj_aligned_cube(vec3r(0, 0, 0), vec3r(10, 10, 10), 5);



	if (!(mat = (t_material*)ft_vector_push_back(&scene->v_material, NULL)))
		return (error_cl_code(CL_OUT_OF_HOST_MEMORY));
	mat->color = vec3f(0.4, 0.2, 0.2);
	mat->reflection = 0;
	mat->refraction = 0;
	mat->texture_id = -1;
	if (!(mat = (t_material*)ft_vector_push_back(&scene->v_material, NULL)))
		return (error_cl_code(CL_OUT_OF_HOST_MEMORY));
	mat->color = vec3f(1, 1, 1);
	mat->reflection = 0.8;
	mat->refraction = 0;
	mat->texture_id = -1;
	if (!(mat = (t_material*)ft_vector_push_back(&scene->v_material, NULL)))
		return (error_cl_code(CL_OUT_OF_HOST_MEMORY));
	mat->color = vec3f(0.1, 0.3, 0.6);
	mat->reflection = 0;
	mat->refraction = 0;
	mat->indice_of_refraction = 0;
	mat->texture_id = -1;
	if (!(mat = (t_material*)ft_vector_push_back(&scene->v_material, NULL)))
		return (error_cl_code(CL_OUT_OF_HOST_MEMORY));
	mat->color = vec3f(0.2, 0.3, 0.7);
	mat->reflection = 0;
	mat->refraction = 0;
	mat->indice_of_refraction = 0;
	mat->texture_id = -1;
	if (!(mat = (t_material*)ft_vector_push_back(&scene->v_material, NULL)))
		return (error_cl_code(CL_OUT_OF_HOST_MEMORY));
	mat->color = vec3f(1, 0.3, 0.3);
	mat->reflection = 1;
	mat->refraction = 0;
	mat->indice_of_refraction = 0;
	mat->texture_id = -1;
	if (!(mat = (t_material*)ft_vector_push_back(&scene->v_material, NULL)))
		return (error_cl_code(CL_OUT_OF_HOST_MEMORY));
	mat->color = vec3f(1, 1, 1);
	mat->reflection = 0.1;
	mat->refraction = 0.65;
	mat->indice_of_refraction = 1.3330;
	mat->texture_id = 0;
	mat->specular = 1;
	mat->specular_color = vec3f(1, 1, 1);
	mat->projection = 1;
	mat->specular_exp = 20;

	if (!(mat = (t_material*)ft_vector_push_back(&scene->v_material, NULL)))
		return (error_cl_code(CL_OUT_OF_HOST_MEMORY));
	mat->color = vec3f(1, 1, 1);
	mat->reflection = 0;
	mat->refraction = 0.8;
	mat->indice_of_refraction = 1;
	mat->texture_id = 0;
	mat->specular = 1;
	mat->specular_color = vec3f(1, 1, 1);
	mat->projection = 1;
	mat->specular_exp = 20;

	if (!(pixels = ft_ppm_file_read("textures/max_val.ppm", &width, &height, &max_val)))
		return (error_string("Could not read ppm file"));
	if (!(texture = (t_texture*)ft_vector_push_back(&scene->v_texture, NULL)))
		return (error_cl_code(CL_OUT_OF_HOST_MEMORY));
	scene->texture_pixels = (cl_uchar*)pixels;
	scene->n_texture_pixels = width * height * (max_val <= 255 ? 1 : 2);
	texture->pixels_offset = 0;
	texture->width = width;
	texture->height = height;
	texture->max_val = max_val;
	texture->filter = e_filter_nearest;

	app->config.screen_size.s[0] = APP_WIDTH;
	app->config.screen_size.s[1] = APP_HEIGHT;
	app->config.color_epsilon = 1.f / 255;
	app->config.intersection_bias = 1e-3;
	app->config.z_far = 20000;

	app->config.ambient_c = vec3f(1, 1, 1);
	app->config.ambient_i = 0.2;
	app->config.camera_light_c = vec3f(1, 1, 1);
	app->config.camera_light_i = 0.2;
	app->config.samples_width = 1;
	app->config.max_depth = 2;
	app->config.projection_depth = 50;
	app->config.post_filters = e_post_filter_none;

	if (!(light = (t_light*)ft_vector_push_back(&scene->v_light, NULL)))
		return (error_cl_code(CL_OUT_OF_HOST_MEMORY));
	light->type = e_light_type_point;
	light->color = vec3f(1, 1, 1);
	light->intensity = 250;
	light->as.point.pos = vec3r(0, 0, 0);

	app->cam.cam_data.pos = vec3r(0, 0, -1);
	return (1);*/
}
