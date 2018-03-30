/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_aligned_cube.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarbi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 22:16:31 by ilarbi            #+#    #+#             */
/*   Updated: 2018/03/29 18:32:31 by ilarbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_obj		obj_aligned_cube(t_real3 pos, t_real3 size, t_mat_id material)
{
	t_obj	obj;
	
	obj.type = type_aligned_cube;
	obj.material_id = material;
	obj.as.aligned_cube.pos = pos;
	obj.as.aligned_cube.size = size;
	return (obj);
}
