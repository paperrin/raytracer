/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec3f.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 14:23:41 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/16 23:34:27 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"
#include <stdlib.h>

t_vec3f			ft_vec3f(float x, float y, float z)
{
	t_vec3f		ret;

	ret.x = x;
	ret.y = y;
	ret.z = z;
	return (ret);
}

t_vec3f			*ft_vec3f_new(float x, float y, float z)
{
	t_vec3f		*ret;

	ret = (t_vec3f*)malloc(sizeof(t_vec3f));
	if (ret)
		*ret = ft_vec3f(x, y, z);
	return (ret);
}

static float	cross_multiply(t_vec3f const *const vec
		, t_matrix const *const mx, int line)
{
	float	ret;
	int		off;

	off = line * MATH_MX_SIZE;
	ret = mx->m[off] * vec->x + mx->m[off + 1]
		* vec->y + mx->m[off + 2] * vec->z;
	ret += mx->m[off + 3];
	return (ret);
}

t_vec3f			ft_vec3f_transform(t_vec3f const *const vec
		, t_matrix const *const mx)
{
	t_vec3f		ret;
	int			w;

	if (!mx || !vec)
		return (ft_vec3f(0, 0, 0));
	w = cross_multiply(vec, mx, 3);
	ret.x = cross_multiply(vec, mx, 0) / w;
	ret.y = cross_multiply(vec, mx, 1) / w;
	ret.z = cross_multiply(vec, mx, 2) / w;
	return (ret);
}

t_vec3f			ft_vec3f_matrix_rot(t_vec3f const *const vec
		, t_matrix const *const mx)
{
	t_vec3f		ret;

	ret.x = vec->x * mx->m[0] + vec->y * mx->m[1] + vec->z * mx->m[2];
	ret.y = vec->x * mx->m[4] + vec->y * mx->m[5] + vec->z * mx->m[6];
	ret.z = vec->x * mx->m[8] + vec->y * mx->m[9] + vec->z * mx->m[10];
	return (ret);
}
