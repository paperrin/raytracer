/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 22:21:23 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/16 21:18:50 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_obj	sphere_default(void)
{
	t_obj	obj;

	obj.type = e_type_sphere;
	obj.material_id = 0;
	obj.as.sphere.pos = vec3r(0, 0, 0);
	obj.as.sphere.up = vec3r(0, 1, 0);
	obj.as.sphere.front = vec3r(0, 0, 1);
	obj.as.sphere.radius = 0.5;
	return (obj);
}

t_obj			*scene_add_sphere(t_scene *const scene, char const *const name)
{
	t_obj		*obj;

	if (!(obj = (t_obj*)scene_map_add(&scene->m_obj, name)))
		return (NULL);
	*obj = sphere_default();
	scene_transform_pos(scene, &obj->as.sphere.pos);
	scene_transform_dir(scene, &obj->as.sphere.up);
	scene_transform_dir(scene, &obj->as.sphere.front);
	return (obj);
}
