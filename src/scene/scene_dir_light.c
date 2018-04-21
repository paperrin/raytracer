/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_dir_light.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 21:05:49 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/21 03:32:50 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_light		dir_light_default(void)
{
	t_light			light;

	light.type = e_light_type_dir;
	light.color = vec3f(1, 1, 1);
	light.intensity = 1;
	light.glare = 0;
	light.dispersion = 0;
	light.as.dir.dir = vec3r(0, -1, 0);
	return (light);
}

t_light				*scene_add_dir_light(t_scene *const scene
		, char const *const name)
{
	t_light			*light;

	if (!(light = (t_light*)scene_map_add(&scene->m_light, name)))
		return (NULL);
	*light = dir_light_default();
	scene_transform_dir(scene, &light->as.dir.dir);
	return (light);
}
