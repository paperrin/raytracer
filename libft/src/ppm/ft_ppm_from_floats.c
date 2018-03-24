/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ppm_from_floats.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarbi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 21:53:30 by ilarbi            #+#    #+#             */
/*   Updated: 2018/03/23 23:50:57 by ilarbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ppm.h"

static unsigned char	*ft_float_to_str(float f, unsigned int max_val,
				unsigned char *s)
{
	unsigned int a;

	f = round(fabs(f * max_val));
	if (!s || max_val < 1 || max_val > 65535)
		return (NULL);
	a = (int)f;
	a = ((a > max_val) ? max_val : a);
	if (max_val <= 255)
	{
		s[0] = (unsigned char)a;
		return (s);
	}
	else
	{
		s[0] = (unsigned char)(a >> 8);
		s[1] = (unsigned char)(a - ((a >> 8) << 8));
		return (s);
	}
	return (NULL);
}

unsigned char			*ft_ppm_from_floats(t_ppm_file *const file, float *ftab)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = ((file->max_val <= 255) ? (1) : (2));
	if (!ftab || !(file->color_depth_vector = (unsigned char *)malloc(
			sizeof(unsigned char) * (file->width * file->height * 3 * size))))
		return (NULL);
	while (i < file->width * file->height * 3)
	{
		if (ft_float_to_str(ftab[i], file->max_val,
				&file->color_depth_vector[i * size]))
			i++;
		else
			return (NULL);
	}
	return (file->color_depth_vector);
}
