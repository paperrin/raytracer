/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec2f_mag.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 19:50:53 by paperrin          #+#    #+#             */
/*   Updated: 2017/10/30 08:09:06 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"
#include <math.h>

float	ft_vec2f_mag(t_vec2f vec)
{
	return (sqrt(ft_vec2f_dot(vec, vec)));
}

float	ft_vec2f_dot(t_vec2f a, t_vec2f b)
{
	return (a.x * b.x + a.y * b.y);
}
