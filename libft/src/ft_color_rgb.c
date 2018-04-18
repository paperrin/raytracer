/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color_rgb.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/07 20:08:06 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/19 01:26:28 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_color.h"

t_color_rgb		ft_color_rgb(unsigned char r, unsigned char g
		, unsigned char b)
{
	t_color_rgb		color;

	color.r = r;
	color.g = g;
	color.b = b;
	return (color);
}

t_color_rgb		ft_color_rgb_add_rgba(t_color_rgb rgb, t_color_rgba rgba)
{
	int		r;
	int		g;
	int		b;
	float	a_base;

	a_base = 1 - rgba.a;
	r = ft_min(255, (rgb.r * a_base + rgba.r * rgba.a));
	g = ft_min(255, (rgb.g * a_base + rgba.g * rgba.a));
	b = ft_min(255, (rgb.b * a_base + rgba.b * rgba.a));
	return (ft_color_rgb(r, g, b));
}

t_color_rgb		ft_color_interpolate(t_color_rgb a, t_color_rgb b, float v)
{
	t_color_rgb		color;

	color.r = a.r + ((int)b.r - a.r) * v;
	color.g = a.g + ((int)b.g - a.g) * v;
	color.b = a.b + ((int)b.b - a.b) * v;
	return (color);
}
