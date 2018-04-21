/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_point_light.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 21:05:48 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/21 03:33:01 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_light		point_light_default(void)
{
	t_light			light;

	light.type = e_light_type_point;
	light.color = vec3f(1, 1, 1);
	light.intensity = 1;
	light.glare = 0;
	light.dispersion = 0;
	light.as.point.pos = vec3r(0, 0, 0);
	return (light);
}

t_light				*scene_add_point_light(t_scene *const scene
		, char const *const name)
{
	t_light			*light;

	if (!(light = (t_light*)scene_map_add(&scene->m_light, name)))
		return (NULL);
	*light = point_light_default();
	scene_transform_pos(scene, &light->as.point.pos);
	return (light);
}
