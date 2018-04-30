/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 21:00:05 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/19 01:31:23 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"

int			image_create(t_image *image, unsigned int width,
		unsigned int height)
{
	const size_t		color_type = GL_RGBA;
	const size_t		color_size = 4;
	size_t				size_bytes;

	size_bytes = sizeof(float) * width * height * color_size;
	if (!(image->pixels = (float*)malloc(size_bytes)))
		return (0);
	ft_bzero(image->pixels, size_bytes);
	image->width = width;
	image->height = height;
	glTexImage2D(GL_TEXTURE_2D, 0, color_size, width, height, 0, color_type,
			GL_FLOAT, (GLvoid*)image->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glEnable(GL_TEXTURE_2D);
	return (1);
}

void		image_destroy(t_image *image)
{
	if (image->pixels)
		free(image->pixels);
}

void		image_put(t_image *image, int x, int y)
{
	const size_t		color_type = GL_RGBA;

	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, image->width, image->height,
			color_type, GL_FLOAT, (GLvoid*)image->pixels);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex2i(x, y);
	glTexCoord2f(0, 1);
	glVertex2i(x, y + image->height);
	glTexCoord2f(1, 1);
	glVertex2i(x + image->width, y + image->height);
	glTexCoord2f(1, 0);
	glVertex2i(x + image->width, y);
	glEnd();
}

void		image_set_pixel(t_image *image, unsigned int x, unsigned int y,
		t_clrf_rgb color)
{
	x = ft_min(x, image->width - 1);
	y = ft_min(y, image->height - 1);
	((t_clrf_rgb*)image->pixels)[y * image->width + x] = color;
}
