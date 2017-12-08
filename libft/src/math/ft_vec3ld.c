/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec3ld.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/06 17:41:28 by paperrin          #+#    #+#             */
/*   Updated: 2017/12/05 15:03:03 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"
#include <stdlib.h>

t_vec3ld			ft_vec3ld(long double x, long double y, long double z)
{
	t_vec3ld		ret;

	ret.x = x;
	ret.y = y;
	ret.z = z;
	return (ret);
}

t_vec3ld			*ft_vec3ld_new(long double x, long double y, long double z)
{
	t_vec3ld		*ret;

	ret = (t_vec3ld*)malloc(sizeof(t_vec3ld));
	if (ret)
		*ret = ft_vec3ld(x, y, z);
	return (ret);
}
