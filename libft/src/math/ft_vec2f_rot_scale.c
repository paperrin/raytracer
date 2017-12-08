/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec2f_rot_scale.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 19:55:42 by paperrin          #+#    #+#             */
/*   Updated: 2017/10/30 08:10:10 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"
#include <math.h>

t_vec2f		ft_vec2f_rot(t_vec2f vec, float angle)
{
	return (ft_vec2f(
		vec.x * cos(angle) - vec.y * sin(angle),
		vec.x * sin(angle) + vec.y * cos(angle)));
}

t_vec2f		ft_vec2f_scale(t_vec2f vec, float scale)
{
	return (ft_vec2f(
		vec.x * scale,
		vec.y * scale));
}
