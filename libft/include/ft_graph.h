/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_graph.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <paperrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 18:57:00 by paperrin          #+#    #+#             */
/*   Updated: 2017/10/21 19:10:49 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GRAPH_H
# define FT_GRAPH_H

# include "ft_math.h"
# include "ft_color.h"
# include "ft_array.h"

typedef struct	s_edge
{
	int				y_max;
	int				y_min;
	int				x;
	t_color_rgb		color_max;
	t_color_rgb		color_min;
	t_color_rgb		color;
	int				sign;
	int				dx;
	int				dy;
	float			sum;
}				t_edge;

typedef struct	s_graph_env
{
	t_array			matrices;
	void			(*f_put_pixel)(t_vec3f pos, t_color_rgb color
			, void *param);
	void			(*f_put_pixel_rgba)(t_vec3f pos, t_color_rgba color
			, void *param);
	void			*put_pixel_param;
	t_color_rgba	fill_rgba;
	t_vec2i			screen_size;
}				t_graph_env;

typedef struct	s_graph_aaline
{
	t_vec2i			a;
	t_vec2i			b;
	t_vec2i			c;
	t_vec2i			d;
	t_vec2i			s;
	int				err;
	int				err2;
	int				w;
	float			ed;
}				t_graph_aaline;

t_array			*ft_graph_create_edge_table(t_vec3f *vertices
	, t_color_rgb *colors, size_t n);
int				ft_graph_poly_fill(t_array *edges
	, void (*f_put_pixel)(t_vec3f pos, t_color_rgb color, void *param)
	, void *param);

int				ft_graph_env_init(t_graph_env **env
	, void (*f_put_pixel)(t_vec3f pos, t_color_rgb color, void *param)
	, void (*f_put_pixel_rgba)(t_vec3f pos, t_color_rgba color, void *param)
	, void *put_pixel_param);
int				ft_graph_push(t_graph_env *env);
void			ft_graph_pop(t_graph_env *env);

void			ft_graph_translate(t_graph_env *env
		, float x, float y, float z);
void			ft_graph_scale(t_graph_env *env, float x, float y, float z);
void			ft_graph_rot_x(t_graph_env *env, float alpha);
void			ft_graph_rot_y(t_graph_env *env, float alpha);
void			ft_graph_rot_z(t_graph_env *env, float alpha);

int				ft_graph_env_rect(t_graph_env *env, t_vec3f pos, t_vec2f size
	, t_color_rgb color);
int				ft_graph_env_crect(t_graph_env *env, t_vec3f pos, t_vec2f size
	, t_color_rgb *colors);
void			ft_graph_env_aaline(t_graph_env *env, t_vec2i a, t_vec2i b
	, float width);

#endif
