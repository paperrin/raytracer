/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec2i.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/07 18:56:33 by paperrin          #+#    #+#             */
/*   Updated: 2017/12/05 14:59:21 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"
#include <stdlib.h>

t_vec2i			ft_vec2i(int x, int y)
{
	t_vec2i		ret;

	ret.x = x;
	ret.y = y;
	return (ret);
}

t_vec2i			*ft_vec2i_new(int x, int y)
{
	t_vec2i		*ret;

	ret = (t_vec2i*)malloc(sizeof(t_vec2i));
	if (ret)
		*ret = ft_vec2i(x, y);
	return (ret);
}

t_vec2i			ft_vec2i_transform(t_vec2i const *const vec
		, t_matrix const *const mx)
{
	t_vec3f		tmp;

	tmp = ft_vec3f(vec->x, vec->y, 1);
	tmp = ft_vec3f_transform(&tmp, mx);
	return (ft_vec2i(round(tmp.x), round(tmp.y)));
}
