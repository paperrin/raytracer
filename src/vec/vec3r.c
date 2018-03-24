/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3r.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 16:31:07 by paperrin          #+#    #+#             */
/*   Updated: 2018/03/24 15:47:36 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

t_real3		vec3r(t_real x, t_real y, t_real z)
{
	t_real3		vec;

	vec.s[0] = x;
	vec.s[1] = y;
	vec.s[2] = z;
	return (vec);
}

t_real		vec3r_dot(t_real3 a, t_real3 b)
{
	return (a.s[0] * b.s[0] + a.s[1] * b.s[1] + a.s[2] * b.s[2]);
}

t_real		vec3r_mag(t_real3 vec)
{
	return (sqrt(vec3r_dot(vec, vec)));
}

t_real3		vec3r_norm(t_real3 vec)
{
	t_real	mag;

	mag = vec3r_mag(vec);
	return (vec3r(vec.s[0] / mag, vec.s[1] / mag, vec.s[2] / mag));
}
