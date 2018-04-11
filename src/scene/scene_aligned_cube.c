/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_aligned_cube.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 22:33:43 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/11 22:41:43 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_obj	aligned_cube_default(void)
{
	t_obj	obj;

	obj.type = e_type_aligned_cube;
	obj.material_id = 0;
	obj.as.aligned_cube.pos = vec3r(0, 0, 0);
	obj.as.aligned_cube.size = vec3r(1, 1, 1);
	return (obj);
}

t_obj			*scene_add_aligned_cube(t_scene *const scene)
{
	t_obj		*obj;

	if (!(obj = (t_obj*)ft_vector_push_back(&scene->v_obj, NULL)))
		return (perror_string(ERR_MEMORY));
	*obj = aligned_cube_default();
	return (obj);
}
