/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec3d_rot.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 21:53:54 by paperrin          #+#    #+#             */
/*   Updated: 2017/11/28 13:55:20 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"
#include <math.h>

t_vec3d		ft_vec3d_rot_z(t_vec3d vec, double angle)
{
	return (ft_vec3d(
		vec.x * cos(angle) - vec.y * sin(angle),
		vec.x * sin(angle) + vec.y * cos(angle),
		vec.z));
}

t_vec3d		ft_vec3d_rot_y(t_vec3d vec, double angle)
{
	return (ft_vec3d(
		vec.x * cos(angle) + vec.z * sin(angle),
		vec.y,
		-vec.x * sin(angle) + vec.z * cos(angle)));
}

t_vec3d		ft_vec3d_rot_x(t_vec3d vec, double angle)
{
	return (ft_vec3d(
		vec.x,
		vec.y * cos(angle) - vec.z * sin(angle),
		vec.y * sin(angle) + vec.z * cos(angle)));
}

t_vec3d		ft_vec3d_rot(t_vec3d vec, double x, double y, double z)
{
	vec = ft_vec3d_rot_x(vec, x);
	vec = ft_vec3d_rot_y(vec, y);
	vec = ft_vec3d_rot_z(vec, z);
	return (vec);
}
