/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_spot_light.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 21:05:50 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/21 19:11:45 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_light		spot_light_default(void)
{
	t_light			light;

	light.type = e_light_type_spot;
	light.color = vec3f(1, 1, 1);
	light.intensity = 1;
	light.glare = 0;
	light.dispersion = 0;
	light.as.spot.pos = vec3r(0, 0, 0);
	light.as.spot.dir = vec3r(0, 1, 0);
	light.as.spot.beam_aperture = 0.3;
	light.as.spot.beam_gradient = 1;
	light.as.spot.field_aperture = 0.6;
	light.as.spot.field_intensity = 0.15;
	return (light);
}

t_light				*scene_add_spot_light(t_scene *const scene
		, char const *const name)
{
	t_light			*light;

	if (!(light = (t_light*)scene_map_add(&scene->m_light, name)))
		return (NULL);
	*light = spot_light_default();
	scene_transform_pos(scene, &light->as.spot.pos);
	scene_transform_dir(scene, &light->as.spot.dir);
	return (light);
}
