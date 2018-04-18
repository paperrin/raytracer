/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clrf_rgb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 21:37:08 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/19 01:28:53 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_color.h"

t_clrf_rgb		ft_clrf_rgba(float r, float g, float b, float a)
{
	t_clrf_rgb		color;

	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
	return (color);
}

t_clrf_rgb		ft_clrf_rgb(float r, float g, float b)
{
	t_clrf_rgb		color;

	color.r = r;
	color.g = g;
	color.b = b;
	color.a = 1;
	return (color);
}

t_clrf_rgb		ft_clrf_rgb_clamp(t_clrf_rgb color)
{
	color.r = ft_clampf(color.r, 0, 1);
	color.g = ft_clampf(color.g, 0, 1);
	color.b = ft_clampf(color.b, 0, 1);
	return (color);
}

t_color_rgb		ft_clrf_rgb_to_rgb(t_clrf_rgb fcolor)
{
	return (ft_color_rgb(fcolor.r * 255, fcolor.g * 255, fcolor.b * 255));
}

unsigned int	ft_clrf_rgb_to_int(t_clrf_rgb fl_color, int endian)
{
	return (ft_color_rgb_to_int(ft_clrf_rgb_to_rgb(fl_color), endian));
}
