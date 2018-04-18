/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 20:58:15 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/18 23:17:42 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		scene_create(t_scene *const scene)
{
	scene->texture_pixels = NULL;
	scene->n_texture_pixels = 0;
	scene->m_obj = scene_map_create(sizeof(t_obj));
	scene->m_light = scene_map_create(sizeof(t_light));
	scene->m_material = scene_map_create(sizeof(t_material));
	scene->m_texture = scene_map_create(sizeof(t_texture));
	scene->v_mx = ft_vector_create(sizeof(t_matrix), NULL, NULL);
	scene->v_mx_r = ft_vector_create(sizeof(t_matrix), NULL, NULL);
	ft_matrix_to_identity(&scene->mx);
	ft_matrix_to_identity(&scene->mx_r);
	return (1);
}

void	scene_destroy(t_scene *const scene)
{
	ft_map_destroy(&scene->m_obj);
	ft_map_destroy(&scene->m_light);
	ft_map_destroy(&scene->m_material);
	ft_map_destroy(&scene->m_texture);
	ft_vector_destroy(&scene->v_mx);
	ft_vector_destroy(&scene->v_mx_r);
	ft_memdel((void**)&scene->texture_pixels);
}

int		scene_load(t_scene *const scene, t_app *const app)
{
	t_light				*light;
	t_material			*mat;
	t_texture			*texture;
	t_obj				*obj;

/*
** Textures
*/
	if (!(texture = scene_add_texture(scene, "tex_brick", "textures/brick.ppm")))
		return (0);
	texture->scale = vec2r(0.2, 0.2);

	if (!(texture = scene_add_texture(scene, "tex_max_val", "textures/max_val.ppm")))
		return (0);

	if (!(texture = scene_add_texture_wave(scene, "tex_wave")))
		return (0);
	texture->scale = vec2r(0.04, 1);

	if (!(texture = scene_add_texture_checkerboard(scene, "tex_checker")))
		return (0);

	if (!(texture = scene_add_texture(scene, "tex_sky", "../textures/park_pano.ppm")))
		return (0);
	texture->as.image.filter = e_filter_bilinear;

/*
** Materials
*/
	if (!(mat = scene_add_material(scene, "mat_brick")))
		return (0);
	mat->color = vec3f(1, 0.0, 0.0);
	mat->reflection = 0;
	mat->refraction = 0;
	if ((mat->texture_id = scene_map_search_index(&scene->m_texture, "tex_brick")) < 0)
		return (error_string("could not find material"));

	if (!(mat = scene_add_material(scene, "mat_max_val")))
		return (0);
	mat->color = vec3f(1, 0.0, 0.0);
	mat->reflection = 0;
	mat->refraction = 0;
	if ((mat->texture_id = scene_map_search_index(&scene->m_texture, "tex_max_val")) < 0)
		return (error_string("could not find material"));

	if (!(mat = scene_add_material(scene, "mat_wave")))
		return (0);
	mat->color = vec3f(1, 0.0, 0.0);
	mat->reflection = 0;
	mat->refraction = 0;
	if ((mat->texture_id = scene_map_search_index(&scene->m_texture, "tex_wave")) < 0)
		return (error_string("could not find material"));

	if (!(mat = scene_add_material(scene, "mat_checker")))
		return (0);
	mat->color = vec3f(1, 0.0, 0.0);
	mat->reflection = 0;
	mat->refraction = 0;
	mat->specular = 1;
	mat->specular_exp = 10;
	if ((mat->texture_id = scene_map_search_index(&scene->m_texture, "tex_checker")) < 0)
		return (error_string("could not find material"));

	if (!(mat = scene_add_material(scene, "mat_floor")))
		return (0);
	mat->color = vec3f(1, 1, 1);
	mat->reflection = 0;
	mat->refraction = 0;
	mat->texture_id = -1;

	if (!(mat = scene_add_material(scene, "mat_sky")))
		return (0);
	mat->color = vec3f(1, 0.0, 0.0);
	mat->reflection = 0;
	mat->refraction = 0;
	mat->specular = 0;
	mat->specular_exp = 10;
	mat->emission = 3;
	mat->ignores_light = 1;
	if ((mat->texture_id = scene_map_search_index(&scene->m_texture, "tex_sky")) < 0)
		return (error_string("could not find material"));

	if (!(mat = scene_add_material(scene, "mat_metal")))
		return (0);
	mat->color = vec3f(1, 1, 1);
	mat->reflection = 0.9;
	mat->refraction = 0;
	mat->specular = 0;
	mat->specular_exp = 100;
	mat->emission = 0.2;
	mat->ignores_light = 0;


/*
** Scene
*/

	scene_translate(scene, 0, 0, 1);

	if (!(obj = scene_add_sphere(scene, NULL)))
		return (0);
	obj->as.sphere.radius = 1000;
	if ((obj->material_id = scene_map_search_index(&scene->m_material, "mat_sky")) < 0)
		return (error_string("could not find material"));
/*
	if (!(obj = scene_add_sphere(scene, NULL)))
		return (0);
	if ((obj->material_id = scene_map_search_index(&scene->m_material, "mat_metal")) < 0)
		return (error_string("could not find material"));
*/
/*
	scene_transform_pop(scene);
	scene_translate(scene, -1, 0, -1);
	if (!(obj = scene_add_sphere(scene, NULL)))
		return (0);
	if ((obj->material_id = scene_map_search_index(&scene->m_material, "mat_brick")) < 0)
		return (error_string("could not find material"));

	scene_transform_pop(scene);
	scene_translate(scene, 1, 0, 1);
	if (!(obj = scene_add_sphere(scene, NULL)))
		return (0);
	if ((obj->material_id = scene_map_search_index(&scene->m_material, "mat_max_val")) < 0)
		return (error_string("could not find material"));

	scene_transform_pop(scene);
	scene_translate(scene, -1, 0, 1);
	if (!(obj = scene_add_aligned_cube(scene, NULL)))
		return (0);
	if ((obj->material_id = scene_map_search_index(&scene->m_material, "mat_wave")) < 0)
		return (error_string("could not find material"));

	scene_transform_pop(scene);
	scene_translate(scene, 1, 0, -1);
	if (!(obj = scene_add_aligned_cube(scene, NULL)))
		return (0);
	if ((obj->material_id = scene_map_search_index(&scene->m_material, "mat_checker")) < 0)
		return (error_string("could not find material"));

	scene_transform_pop(scene);
	scene_translate(scene, 2, 0, 0);
	if (!(obj = scene_add_cylinder(scene, NULL)))
		return (0);
	if ((obj->material_id = scene_map_search_index(&scene->m_material, "mat_checker")) < 0)
		return (error_string("could not find material"));

	scene_transform_pop(scene);
	scene_translate(scene, -2, 0, 0);
	if (!(obj = scene_add_cone(scene, NULL)))
		return (0);
	if ((obj->material_id = scene_map_search_index(&scene->m_material, "mat_wave")) < 0)
		return (error_string("could not find material"));
*/
	/*
	scene_transform_pop(scene);
	scene_translate(scene, 0, 2, -2);
	scene_rotate(scene, M_PI / 2, 0, 0);
	if (!(light = scene_add_point_light(scene, NULL)))
		return (0);
	light->intensity = 80;
	light->fallback = 1;
	light->glare = 0;
*/
	scene_transform_pop(scene);
	scene_translate(scene, 0, 2, 0);
	if (!(light = scene_add_dir_light(scene, NULL)))
		return (0);
	light->intensity = 1;
	light->fallback = 0;
	light->glare = 0.5;
	light->as.dir.dir = vec3r_norm(vec3r(0.5, -1, 1));

	app->config.screen_size.s[0] = APP_WIDTH;
	app->config.screen_size.s[1] = APP_HEIGHT;
	app->config.color_epsilon = 1.f / 255;
	app->config.intersection_bias = 1e-3;
	app->config.z_far = 20000;

	app->config.ambient_c = vec3f(1, 1, 1);
	app->config.ambient_i = 0.025;
	app->config.camera_light_c = vec3f(1, 1, 1);
	app->config.camera_light_i = 0.025;
	app->config.samples_width = 1;
	app->config.max_depth = 1;
	app->config.projection_depth = 0;
	app->config.post_filters = e_post_filter_none;

	scene_add_camera(scene, app);
	scene_transform_pop(scene);

	return (1);
}
