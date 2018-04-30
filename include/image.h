/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 15:25:25 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/16 02:38:58 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_H
# define IMAGE_H

# include "GLFW/glfw3.h"
# include "window.h"

/*
** Image object, must be initialized by image_create()
**
** @var pixels - array of float quadruples in the RGBA format representing
** image pixels in row-major order
** @var width - width of the image in pixels
** @var height - height of the image in pixels
*/
typedef struct		s_image
{
	float			*pixels;
	unsigned int	width;
	unsigned int	height;
}					t_image;

/*
** Creates a black filled image
**
** @param image - a pointer to the #t_image object to initialize
** @param width - the width of the image in pixels
** @param height - the height of the image in pixels
** @return FALSE if the image creation failed, TRUE otherwise
*/
int					image_create(t_image *image, unsigned int width,
		unsigned int height);

/*
** Destroys an image
**
** @param image - a pointer to the #t_image object that should get destroyed
*/
void				image_destroy(t_image *image);

/*
** Puts an image to the current active window
**
** @param image - a pointer to the concerned #t_image
** @param x - the top left x position the image should get put at on the window
** @param y - the top left y position the image should get put at on the window
*/
void				image_put(t_image *image, int x, int y);

/*
** Sets an image's pixel to the given color
**
** @param image - a pointer to the concerned #t_image
** @param x - the image x position of the pixel that should be set
** @param y - the image y position of the pixel that should be set
** @param color - the color the pixel should be set to
*/
void				image_set_pixel(t_image *image, unsigned int x,
		unsigned int y, t_clrf_rgb color);

#endif
