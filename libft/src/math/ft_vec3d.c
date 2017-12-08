/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/06 17:41:28 by paperrin          #+#    #+#             */
/*   Updated: 2017/12/05 15:02:18 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"
#include <stdlib.h>

t_vec3d			ft_vec3d(double x, double y, double z)
{
	t_vec3d		ret;

	ret.x = x;
	ret.y = y;
	ret.z = z;
	return (ret);
}

t_vec3d			*ft_vec3d_new(double x, double y, double z)
{
	t_vec3d		*ret;

	ret = (t_vec3d*)malloc(sizeof(t_vec3d));
	if (ret)
		*ret = ft_vec3d(x, y, z);
	return (ret);
}
