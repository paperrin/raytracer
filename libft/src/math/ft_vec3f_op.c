/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec3f_op.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 21:50:13 by paperrin          #+#    #+#             */
/*   Updated: 2017/11/06 22:00:25 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"

t_vec3f		ft_vec3f_add(t_vec3f a, t_vec3f b)
{
	return (ft_vec3f(a.x + b.x, a.y + b.y, a.z + b.z));
}

t_vec3f		ft_vec3f_sub(t_vec3f a, t_vec3f b)
{
	return (ft_vec3f(a.x - b.x, a.y - b.y, a.z - b.z));
}

t_vec3f		ft_vec3f_mult(t_vec3f a, t_vec3f b)
{
	return (ft_vec3f(a.x * b.x, a.y * b.y, a.z * b.z));
}
