/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 22:21:23 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/28 21:36:07 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_obj	sphere_default(void)
{
	t_obj	obj;

	obj.type = e_type_sphere;
	obj.material_id = 0;
	obj.pos = vec3r(0, 0, 0);
	obj.up = vec3r(0, 1, 0);
	obj.normal = vec3r(0, 0, -1);
	obj.as.sphere.radius = 0.5;
	return (obj);
}

t_obj			*scene_add_sphere(t_scene *const scene, char const *const name)
{
	t_obj		*obj;

	if (!(obj = (t_obj*)scene_map_add(&scene->m_obj, name)))
		return (NULL);
	*obj = sphere_default();
	scene_transform_pos(scene, &obj->pos);
	scene_transform_dir(scene, &obj->up);
	scene_transform_dir(scene, &obj->normal);
	return (obj);
}
