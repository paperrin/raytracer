/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color_hsv_to_rgb.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/07 19:17:48 by paperrin          #+#    #+#             */
/*   Updated: 2017/10/21 19:12:16 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_color.h"

t_color_rgb			ft_color_hsv_to_rgb(t_color_hsv hsv)
{
	int				region;
	float			l;
	float			m;
	float			n;
	float			f;

	region = floor((float)hsv.h / 60);
	f = ((float)hsv.h / 60) - region;
	l = ((float)hsv.v / 100) * (1 - ((float)hsv.s / 100));
	m = ((float)hsv.v / 100) * (1 - f * ((float)hsv.s / 100));
	n = ((float)hsv.v / 100) * (1 - (1 - f) * ((float)hsv.s / 100));
	if (region == 0)
		return (ft_color_rgb(((float)hsv.v / 100) * 255, n * 255, l * 255));
	else if (region == 1)
		return (ft_color_rgb(m * 255, ((float)hsv.v / 100) * 255, l * 255));
	else if (region == 2)
		return (ft_color_rgb(l * 255, ((float)hsv.v / 100) * 255, n * 255));
	else if (region == 3)
		return (ft_color_rgb(l * 255, m * 255, ((float)hsv.v / 100) * 255));
	else if (region == 4)
		return (ft_color_rgb(n * 255, l * 255, ((float)hsv.v / 100) * 255));
	else
		return (ft_color_rgb(((float)hsv.v / 100) * 255, l * 255, m * 255));
}
