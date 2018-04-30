/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_material.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 19:49:09 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/28 21:02:52 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_material	material_default(void)
{
	t_material		material;

	material.color = vec3f(1, 1, 1);
	material.reflection = 0;
	material.refraction = 0;
	material.emission = 0;
	material.ignores_light = 0;
	material.specular = 0;
	material.specular_color = vec3f(1, 1, 1);
	material.specular_exp = 100;
	material.refraction_index = 1;
	material.projection = 0;
	material.texture_id = -1;
	material.refraction_map_id = -1;
	return (material);
}

t_material			*scene_add_material(t_scene *const scene
		, char const *const name)
{
	t_material		*mat;

	if (!(mat = (t_material*)scene_map_add(&scene->m_material, name)))
		return (NULL);
	*mat = material_default();
	return (mat);
}
