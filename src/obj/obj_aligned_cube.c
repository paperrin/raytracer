/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_aligned_cube.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarbi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 22:16:31 by ilarbi            #+#    #+#             */
/*   Updated: 2018/04/08 23:11:16 by ilarbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_obj		obj_aligned_cube(t_real3 pos, t_real3 size, t_mat_id material)
{
	t_obj	obj;
	
	obj.type = e_type_aligned_cube;
	obj.material_id = material;
	obj.as.aligned_cube.pos = pos;
	obj.as.aligned_cube.size = size;
	return (obj);
}
