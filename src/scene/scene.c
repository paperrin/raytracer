/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 20:58:15 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/21 22:18:25 by paperrin         ###   ########.fr       */
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
	t_texture			*texture;
	/*t_material			*material;
	t_obj				*obj;
	int					i;


	material = scene_add_material(scene, "mat");
	i = -1;
	while (++i < 50)
	{
		scene_rotate(scene, 0, 0.1, 0);
		scene_translate(scene, 0, 0.1, 0);
		scene_transform_push(scene);
		scene_translate(scene, 0, 0, 1);
		obj = scene_add_sphere(scene, NULL);
		obj->material_id = scene_map_search_index(&scene->m_material, "mat");
		scene_transform_pop(scene);
	}*/

	if (!(texture = scene_add_texture(scene, "tex_brick", "textures/brick.ppm")))
		return (0);
	texture->scale = vec2r(0.2, 0.2);
	if (!(texture = scene_add_texture(scene, "tex_pano", "../textures/park_pano.ppm")))
		return (0);
	if (!(texture = scene_add_texture_wave(scene, "tex_wave")))
		return (0);
	texture->scale = vec2r(0.04, 1);
	if (!(texture = scene_add_texture_checkerboard(scene, "tex_checker")))
		return (0);
	scene_add_camera(scene, app);
	return (1);
}
