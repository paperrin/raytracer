/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color_hsv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/07 19:53:52 by paperrin          #+#    #+#             */
/*   Updated: 2017/12/05 14:54:14 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_color.h"

t_color_hsv		ft_color_hsv(unsigned short h, unsigned char s
		, unsigned char v)
{
	t_color_hsv		color;

	color.h = h % 361;
	color.s = s % 101;
	color.v = v % 101;
	return (color);
}
