/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec3f_mag.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 13:47:45 by paperrin          #+#    #+#             */
/*   Updated: 2017/11/05 22:36:01 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"
#include <math.h>

float	ft_vec3f_mag(t_vec3f vec)
{
	return (sqrt(ft_vec3f_dot(vec, vec)));
}

float	ft_vec3f_dot(t_vec3f a, t_vec3f b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec3f	ft_vec3f_norm(t_vec3f vec)
{
	float		mag;

	mag = ft_vec3f_mag(vec);
	return (ft_vec3f(vec.x / mag, vec.y / mag, vec.z / mag));
}
