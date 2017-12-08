/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec3d_rot_scale.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 13:49:24 by paperrin          #+#    #+#             */
/*   Updated: 2017/11/10 21:14:27 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"
#include <math.h>

t_vec3d		ft_vec3d_scale(t_vec3d vec, double scale)
{
	return (ft_vec3d(
		vec.x * scale,
		vec.y * scale,
		vec.z * scale));
}

t_vec3d		ft_vec3d_div_by(t_vec3d vec, double scale)
{
	return (ft_vec3d(
		vec.x / scale,
		vec.y / scale,
		vec.z / scale));
}
