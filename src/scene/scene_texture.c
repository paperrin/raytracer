/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 00:44:23 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/28 21:10:54 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "ppm.h"

static int			scene_add_texture_pixels(t_scene *const scene,
		unsigned char *pixels, size_t size)
{
	unsigned char	*new;
	size_t			new_size;

	new_size = scene->n_texture_pixels + size;
	if (!(new = (unsigned char*)malloc(sizeof(unsigned char) * new_size * 3)))
		return (error_string(ERR_MEMORY));
	if (scene->texture_pixels)
		ft_memcpy(new, scene->texture_pixels, scene->n_texture_pixels * 3);
	ft_memcpy(&new[scene->n_texture_pixels * 3], pixels, size * 3);
	ft_memdel((void**)&scene->texture_pixels);
	scene->texture_pixels = new;
	scene->n_texture_pixels = new_size;
	return (1);
}

static int			scene_texture_load_from_file(t_scene *const scene,
		t_texture *const texture, char const *const path)
{
	unsigned char		*pixels;
	size_t				width;
	size_t				height;
	unsigned int		max_val;

	if (!(pixels = ft_ppm_file_read(path, &width, &height, &max_val)))
		return (error_string_2("could not open ppm file", path));
	texture->type = e_texture_type_image;
	texture->as.image.pixels_offset = scene->n_texture_pixels;
	texture->as.image.width = width;
	texture->as.image.height = height;
	texture->as.image.max_val = max_val;
	texture->as.image.filter = e_filter_nearest;
	texture->translate = vec2r(0, 0);
	texture->scale = vec2r(1, 1);
	if (!scene_add_texture_pixels(scene, pixels,
				width * height * (max_val <= 255 ? 1 : 2)))
	{
		ft_memdel((void**)&pixels);
		return (0);
	}
	ft_memdel((void**)&pixels);
	return (1);
}

int					scene_add_default_texture(t_scene *const scene)
{
	unsigned char const	pixels[3 * 4] = {255, 0, 0, 0, 255, 0
		, 0, 0, 255, 255, 255, 255};
	t_texture			*tex;

	if (scene_map_search(&scene->m_texture, "default"))
		return (1);
	if (!(tex = (t_texture*)scene_map_add(&scene->m_texture, "default")))
		return (0);
	tex->type = e_texture_type_image;
	tex->as.image.pixels_offset = scene->n_texture_pixels;
	tex->as.image.width = 2;
	tex->as.image.height = 2;
	tex->as.image.max_val = 255;
	tex->as.image.filter = e_filter_nearest;
	tex->translate = vec2r(0, 0);
	tex->scale = vec2r(1, 1);
	if (!scene_add_texture_pixels(scene, (unsigned char *)pixels
				, tex->as.image.width * tex->as.image.height
				* (tex->as.image.max_val <= 255 ? 1 : 2)))
		return (0);
	return (1);
}

t_texture			*scene_add_texture(t_scene *const scene,
		char const *const name, char const *const path)
{
	t_texture		*tex;

	if (!(tex = (t_texture*)scene_map_add(&scene->m_texture, name)))
		return (NULL);
	if (!scene_texture_load_from_file(scene, tex, path))
		return (NULL);
	return (tex);
}
