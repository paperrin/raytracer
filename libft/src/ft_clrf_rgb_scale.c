/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clrf_rgb_scale.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 15:22:58 by paperrin          #+#    #+#             */
/*   Updated: 2017/11/28 15:23:09 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_color.h"

t_clrf_rgb		ft_clrf_rgb_scale(t_clrf_rgb c, float scale)
{
	return (ft_clrf_rgba(c.r * scale, c.g * scale, c.b * scale, c.a * scale));
}

t_clrf_rgb		ft_clrf_rgb_div_by(t_clrf_rgb c, float div)
{
	return (ft_clrf_rgba(c.r / div, c.g / div, c.b / div, c.a / div));
}
