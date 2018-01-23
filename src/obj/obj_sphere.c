/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 16:22:11 by paperrin          #+#    #+#             */
/*   Updated: 2018/01/23 04:01:52 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_obj		obj_sphere(t_real3 pos, t_real radius, t_mat_id material)
{
	t_obj		obj;

	obj.type = type_sphere;
	obj.material_id = material;
	obj.as.sphere.pos = pos;
	obj.as.sphere.up = vec3r(0, 1, 0);
	obj.as.sphere.front = vec3r(0, 0, 1);
	obj.as.sphere.radius = radius;
	return (obj);
}
