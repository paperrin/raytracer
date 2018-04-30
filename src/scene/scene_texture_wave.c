/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_texture_wave.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 21:02:17 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/18 02:39:59 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_texture	texture_wave_default(void)
{
	t_texture		tex;

	tex.type = e_texture_type_sine;
	tex.translate = vec2r(0, 0);
	tex.scale = vec2r(1, 1);
	tex.as.sine.color1 = vec3f(0, 0, 0);
	tex.as.sine.color2 = vec3f(1, 1, 1);
	tex.as.sine.color3 = vec3f(0, 0, 0);
	tex.as.sine.color4 = vec3f(1, 1, 1);
	tex.as.sine.factors = vec2r(1, 0);
	return (tex);
}

t_texture			*scene_add_texture_wave(t_scene *const scene,
		char const *const name)
{
	t_texture		*tex;

	if (!(tex = (t_texture*)scene_map_add(&scene->m_texture, name)))
		return (NULL);
	*tex = texture_wave_default();
	return (tex);
}
