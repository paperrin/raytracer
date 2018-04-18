/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color_rgb_op.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 23:43:51 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/19 01:27:25 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_color.h"

t_color_rgb		ft_color_rgb_add(t_color_rgb ca, t_color_rgb cb)
{
	int		r;
	int		g;
	int		b;

	r = ft_min((ca.r + cb.r) / 2, 255);
	g = ft_min((ca.g + cb.g) / 2, 255);
	b = ft_min((ca.b + cb.b) / 2, 255);
	return (ft_color_rgb(r, g, b));
}

t_color_rgb		ft_color_rgb_scale(t_color_rgb c, double scale)
{
	int		r;
	int		g;
	int		b;

	r = ft_min(c.r * scale, 255);
	g = ft_min(c.g * scale, 255);
	b = ft_min(c.b * scale, 255);
	return (ft_color_rgb(r, g, b));
}
