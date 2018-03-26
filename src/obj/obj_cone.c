/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabgrall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 17:43:16 by eabgrall          #+#    #+#             */
/*   Updated: 2018/03/26 19:12:38 by eabgrall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_obj		obj_cone(t_real3 pos, t_real angle, t_real3 up, t_mat_id material)
{
	t_obj		obj;

	obj.type = type_cone;
	obj.material_id = material;
	obj.as.cone.pos = pos;
	obj.as.cone.normal = up;
	obj.as.cone.up = up;
	obj.as.cone.angle = angle;
	return (obj);
}
