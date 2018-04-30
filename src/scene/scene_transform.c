/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_transform.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 19:20:33 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/16 23:29:25 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	scene_rotate(t_scene *const scene, float x, float y, float z)
{
	ft_matrix_rot(&scene->mx, x, y, z);
	ft_matrix_rot(&scene->mx_r, x, y, z);
}

void	scene_transform(t_real3 *const v3r,
		t_matrix const *const mx)
{
	t_vec3f		tmp;

	tmp = ft_vec3f((float)v3r->s[0], (float)v3r->s[1], (float)v3r->s[2]);
	tmp = ft_vec3f_transform(&tmp, mx);
	*v3r = vec3r((t_real)tmp.x, (t_real)tmp.y, (t_real)tmp.z);
}

void	scene_translate(t_scene *const scene, float x, float y, float z)
{
	ft_matrix_translate(&scene->mx, x, y, z);
}

void	scene_transform_pos(t_scene const *const scene, t_real3 *const vec3r)
{
	scene_transform(vec3r, &scene->mx);
}

void	scene_transform_dir(t_scene const *const scene, t_real3 *const vec3r)
{
	scene_transform(vec3r, &scene->mx_r);
	*vec3r = vec3r_norm(*vec3r);
}
