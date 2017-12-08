/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color_rgb_to_int.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 23:54:07 by paperrin          #+#    #+#             */
/*   Updated: 2017/11/11 01:40:16 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_color.h"

unsigned int	ft_color_rgb_to_int(t_color_rgb color, int endian)
{
	unsigned int	encoded;

	encoded = 0;
	if (endian == 0)
	{
		encoded |= color.b;
		encoded |= color.g << 8;
		encoded |= color.r << 16;
	}
	else
	{
		encoded |= color.r << 8;
		encoded |= color.g << 16;
		encoded |= color.b << 24;
	}
	return (encoded);
}
