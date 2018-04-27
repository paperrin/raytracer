/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_texture_noise.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 08:28:27 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/27 09:14:54 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_texture	texture_noise_default(void)
{
	t_texture		tex;

	tex.type = e_texture_type_noise;
	tex.translate = vec2r(0, 0);
	tex.scale = vec2r(1, 1);
	tex.as.noise.color1 = vec3f(0, 0, 0);
	tex.as.noise.color2 = vec3f(1, 1, 1);
	return (tex);
}

t_texture			*scene_add_texture_noise(t_scene *const scene,
		char const *const name)
{
	t_texture		*tex;

	if (!(tex = (t_texture*)scene_map_add(&scene->m_texture, name)))
		return (NULL);
	*tex = texture_noise_default();
	return (tex);
}
