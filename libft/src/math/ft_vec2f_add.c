/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec2f_add.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 19:45:07 by paperrin          #+#    #+#             */
/*   Updated: 2017/10/30 08:08:45 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"

t_vec2f		ft_vec2f_add(t_vec2f a, t_vec2f b)
{
	return (ft_vec2f(a.x + b.x, a.y + b.y));
}

t_vec2f		ft_vec2f_sub(t_vec2f a, t_vec2f b)
{
	return (ft_vec2f(a.x - b.x, a.y - b.y));
}

t_vec2f		ft_vec2f_mult(t_vec2f a, t_vec2f b)
{
	return (ft_vec2f(a.x * b.x, a.y * b.y));
}
