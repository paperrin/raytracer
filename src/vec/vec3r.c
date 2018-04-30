/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3r.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 16:31:07 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/16 23:36:01 by paperrin         ###   ########.fr       */
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
	return (sqrtf(vec3r_dot(vec, vec)));
}

t_real3		vec3r_norm(t_real3 vec)
{
	t_real		mag;

	mag = vec3r_mag(vec);
	vec.s[0] = vec.s[0] / mag;
	vec.s[1] = vec.s[1] / mag;
	vec.s[2] = vec.s[2] / mag;
	return (vec);
}

t_real3		vec3r_matrix_rot(t_real3 v3r, t_matrix const *const mx)
{
	t_vec3f		tmp;
	t_real3		ret;

	tmp = ft_vec3f((float)v3r.s[0], (float)v3r.s[1], (float)v3r.s[2]);
	tmp = ft_vec3f_matrix_rot(&tmp, mx);
	ret = vec3r((t_real)tmp.x, (t_real)tmp.y, (t_real)tmp.z);
	return (ret);
}
