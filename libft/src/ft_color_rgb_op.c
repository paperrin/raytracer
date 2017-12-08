/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color_rgb_op.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 23:43:51 by paperrin          #+#    #+#             */
/*   Updated: 2017/11/07 00:25:40 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_color.h"

t_color_rgb		ft_color_rgb_add(t_color_rgb ca, t_color_rgb cb)
{
	int		r;
	int		g;
	int		b;

	r = MIN((ca.r + cb.r) / 2, 255);
	g = MIN((ca.g + cb.g) / 2, 255);
	b = MIN((ca.b + cb.b) / 2, 255);
	return (ft_color_rgb(r, g, b));
}

t_color_rgb		ft_color_rgb_scale(t_color_rgb c, double scale)
{
	int		r;
	int		g;
	int		b;

	r = MIN(c.r * scale, 255);
	g = MIN(c.g * scale, 255);
	b = MIN(c.b * scale, 255);
	return (ft_color_rgb(r, g, b));
}
