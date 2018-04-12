/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 22:28:27 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/12 18:52:56 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_obj	plane_default(void)
{
	t_obj	obj;

	obj.type = e_type_plane;
	obj.material_id = 0;
	obj.as.plane.pos = vec3r(0, 0, 0);
	obj.as.plane.normal = vec3r(1, 0, 0);
	obj.as.plane.up = vec3r(0, 1, 0);
	return (obj);
}

t_obj			*scene_add_plane(t_scene *const scene)
{
	t_obj		*obj;

	if (!(obj = (t_obj*)ft_vector_push_back(&scene->v_obj, NULL)))
		return (perror_string(ERR_MEMORY));
	*obj = plane_default();
	scene_transform_pos(scene, &obj->as.plane.pos);
	scene_transform_dir(scene, &obj->as.plane.normal);
	scene_transform_dir(scene, &obj->as.plane.up);
	return (obj);
}
