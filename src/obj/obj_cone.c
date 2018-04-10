/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_cone.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabgrall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/19 17:43:16 by eabgrall          #+#    #+#             */
/*   Updated: 2018/03/30 21:30:40 by eabgrall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_obj		obj_cone(t_real3 pos, t_real3 up, t_real3 normal, t_real angle)
{
	t_obj		obj;

	obj.type = type_cone;
	obj.material_id = 0;
	obj.as.cone.pos = pos;
	obj.as.cone.up = up;
	obj.as.cone.normal = normal;
	obj.as.cone.angle = angle;
	return (obj);
}
