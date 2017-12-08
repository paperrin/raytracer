/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec3f_scale.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 21:56:12 by paperrin          #+#    #+#             */
/*   Updated: 2017/11/06 21:56:22 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"
#include <math.h>

t_vec3f		ft_vec3f_scale(t_vec3f vec, float scale)
{
	return (ft_vec3f(
		vec.x * scale,
		vec.y * scale,
		vec.z * scale));
}
