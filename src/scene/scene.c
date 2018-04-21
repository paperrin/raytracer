/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 20:58:15 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/21 18:03:23 by ilarbi           ###   ########.fr       */
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
	scene_add_camera(scene, app);
	scene_transform_pop(scene);
	return (1);
}
