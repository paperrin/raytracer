/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_graph_env_rect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <paperrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 09:00:07 by paperrin          #+#    #+#             */
/*   Updated: 2017/10/07 03:11:29 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_graph.h"

static void			set_vertices(t_vec3f *vertices, t_vec3f *pos, t_vec2f *size)
{
	vertices[0] = ft_vec3f(pos->x, pos->y, pos->z);
	vertices[1] = ft_vec3f(pos->x + size->x, pos->y, pos->z);
	vertices[2] = ft_vec3f(pos->x + size->x, pos->y + size->y, pos->z);
	vertices[3] = ft_vec3f(pos->x, pos->y + size->y, pos->z);
}

static void			apply_transforms(t_graph_env *env, t_vec3f *vertices)
{
	int			i;

	if (!env->matrices.size)
		return ;
	i = -1;
	while (++i < 4)
	{
		vertices[i] = ft_vec3f_transform(&vertices[i]
			, (t_matrix*)ft_array_back(&env->matrices));
	}
}

int					ft_graph_env_crect(t_graph_env *env, t_vec3f pos
	, t_vec2f size, t_color_rgb *colors)
{
	t_vec3f		vertices[4];

	set_vertices(vertices, &pos, &size);
	apply_transforms(env, vertices);
	if (!ft_graph_poly_fill(ft_graph_create_edge_table(vertices, colors, 4)
			, env->f_put_pixel, env->put_pixel_param))
		return (0);
	return (1);
}

int					ft_graph_env_rect(t_graph_env *env, t_vec3f pos
	, t_vec2f size, t_color_rgb color)
{
	t_color_rgb		colors[4];
	int				i;

	i = 4;
	while (--i >= 0)
		colors[i] = color;
	return (ft_graph_env_crect(env, pos, size, colors));
}
