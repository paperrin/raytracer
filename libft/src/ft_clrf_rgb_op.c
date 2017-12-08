/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clrf_rgb_op.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 00:30:33 by paperrin          #+#    #+#             */
/*   Updated: 2017/11/28 15:22:43 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_color.h"

t_clrf_rgb		ft_clrf_rgb_add(t_clrf_rgb c1, t_clrf_rgb c2)
{
	return (ft_clrf_rgba(c1.r + c2.r, c1.g + c2.g, c1.b + c2.b, c1.a + c2.a));
}

t_clrf_rgb		ft_clrf_rgb_sub(t_clrf_rgb c1, t_clrf_rgb c2)
{
	return (ft_clrf_rgba(c1.r - c2.r, c1.g - c2.g, c1.b - c2.b, c1.a - c2.a));
}

t_clrf_rgb		ft_clrf_rgb_mult(t_clrf_rgb c1, t_clrf_rgb c2)
{
	return (ft_clrf_rgba(c1.r * c2.r, c1.g * c2.g, c1.b * c2.b, c1.a * c2.a));
}

t_clrf_rgb		ft_clrf_rgb_div(t_clrf_rgb c1, t_clrf_rgb c2)
{
	return (ft_clrf_rgba(c1.r / c2.r, c1.g / c2.g, c1.b / c2.b, c1.a / c2.a));
}
