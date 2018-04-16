/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_material.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 19:49:09 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/16 02:27:52 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_material	material_default(void)
{
	t_material		material;

	material.color = vec3f(1, 1, 1);
	material.reflection = 0;
	material.refraction = 0;
	material.specular = 0;
	material.specular_color = vec3f(1, 1, 1);
	material.specular_exp = 100;
	material.refraction_index = 1;
	material.projection = 1;
	material.texture_id = -2;
	return (material);
}

t_material			*scene_add_material(t_scene *const scene, char const *const name)
{
	t_material		*mat;

	if (!(mat = (t_material*)scene_map_add(&scene->m_material, name)))
		return (NULL);
	*mat = material_default();
	return (mat);
}
