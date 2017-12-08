/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec3d_mag.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 21:50:49 by paperrin          #+#    #+#             */
/*   Updated: 2017/11/30 15:04:00 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"
#include <math.h>

double		ft_vec3d_mag(t_vec3d vec)
{
	return (sqrt(ft_vec3d_dot(vec, vec)));
}

double		ft_vec3d_dot(t_vec3d a, t_vec3d b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec3d		ft_vec3d_norm(t_vec3d vec)
{
	double		mag;

	mag = ft_vec3d_mag(vec);
	return (ft_vec3d(vec.x / mag, vec.y / mag, vec.z / mag));
}
