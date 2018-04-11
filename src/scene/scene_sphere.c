/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 22:21:23 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/11 23:00:28 by paperrin         ###   ########.fr       */
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

t_obj			*scene_add_sphere(t_scene *const scene)
{
	t_obj		*obj;

	if (!(obj = (t_obj*)ft_vector_push_back(&scene->v_obj, NULL)))
		return (perror_string(ERR_MEMORY));
	*obj = sphere_default();
	scene_transform_real3(scene, &obj->as_sphere.pos);
	scene_transform_real3(scene, &obj->as_sphere.up);
	scene_transform_real3(scene, &obj->as_sphere.front);
	return (obj);
}
