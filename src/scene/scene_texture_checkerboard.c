/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_texture_checkerboard.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 21:08:19 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/22 20:19:31 by ilarbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_texture	texture_checkerboard_default(void)
{
	t_texture		tex;

	tex.type = e_texture_type_checkerboard;
	tex.translate = vec2r(0, 0);
	tex.scale = vec2r(1, 1);
	tex.as.sine.color1 = vec3f(0, 0, 0);
	tex.as.sine.color2 = vec3f(1, 1, 1);
	return (tex);
}

t_texture			*scene_add_texture_checkerboard(t_scene *const scene,
		char const *const name)
{
	t_texture		*tex;

	if (!(tex = (t_texture*)scene_map_add(&scene->m_texture, name)))
		return (NULL);
	*tex = texture_checkerboard_default();
	return (tex);
}
