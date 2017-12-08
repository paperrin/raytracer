/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec3d_op.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 21:49:10 by paperrin          #+#    #+#             */
/*   Updated: 2017/11/26 22:45:13 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"

t_vec3d		ft_vec3d_add(t_vec3d a, t_vec3d b)
{
	return (ft_vec3d(a.x + b.x, a.y + b.y, a.z + b.z));
}

t_vec3d		ft_vec3d_sub(t_vec3d a, t_vec3d b)
{
	return (ft_vec3d(a.x - b.x, a.y - b.y, a.z - b.z));
}

t_vec3d		ft_vec3d_mult(t_vec3d a, t_vec3d b)
{
	return (ft_vec3d(a.x * b.x, a.y * b.y, a.z * b.z));
}

t_vec3d		ft_vec3d_cross(t_vec3d a, t_vec3d b)
{
	return (ft_vec3d(a.y * b.z - a.z * b.y
				, a.z * b.x - a.x * b.z
				, a.x * b.y - a.y * b.x));
}
