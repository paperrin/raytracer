/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color_hsl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/07 20:00:57 by paperrin          #+#    #+#             */
/*   Updated: 2017/12/05 14:53:15 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_color.h"

t_color_hsl		ft_color_hsl(unsigned short h, unsigned char s
		, unsigned char l)
{
	t_color_hsl		color;

	color.h = h % 361;
	color.s = s % 101;
	color.l = l % 101;
	return (color);
}
