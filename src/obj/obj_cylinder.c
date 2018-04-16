/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabgrall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 19:05:24 by eabgrall          #+#    #+#             */
/*   Updated: 2018/04/13 23:24:29 by eabgrall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_obj			obj_cylinder(t_real3 pos, t_real3 up, t_real3 normal,
		t_real radius, t_mat_id material)
{
	t_obj		obj;

	obj.type = e_type_cylinder;
	obj.material_id = material;
	obj.as.cylinder.pos = pos;
	obj.as.cylinder.up = up;
	obj.as.cylinder.normal = normal;
	obj.as.cylinder.radius = radius;
	return (obj);
}
