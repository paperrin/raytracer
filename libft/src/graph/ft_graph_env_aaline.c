/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_graph_env_aaline.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <paperrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/09 02:36:07 by paperrin          #+#    #+#             */
/*   Updated: 2017/10/16 12:44:09 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_graph.h"

static void		plot(t_graph_env *env, int x, int y, float a)
{
	t_color_rgba	rgba;

	a = 1 - MIN(1, a);
	rgba = ft_color_rgba(env->fill_rgba.r, env->fill_rgba.g, env->fill_rgba.b
			, env->fill_rgba.a * a);
	(*env->f_put_pixel_rgba)(ft_vec3f(x, y, 0), rgba, env->put_pixel_param);
}

static int		step_x(t_graph_env *env, t_graph_aaline *l)
{
	if (2 * l->err2 >= -l->d.x)
	{
		l->err2 += l->d.y;
		l->c.y = l->a.y;
		while (l->err2 <= l->ed * l->w && (l->b.y != l->c.y || l->d.x > l->d.y))
		{
			l->c.y += l->s.y;
			plot(env, l->a.x, l->c.y, abs(l->err2) / l->ed - l->w + 1);
			if (l->d.y == 0)
				plot(env, l->a.x, l->a.y + (l->a.y - l->c.y)
					, abs(l->err2) / l->ed - l->w + 1);
			l->err2 += l->d.x;
		}
		if (l->a.x == l->b.x)
			return (0);
		l->err2 = l->err;
		l->err -= l->d.y;
		l->a.x += l->s.x;
	}
	return (1);
}

static int		step_y(t_graph_env *env, t_graph_aaline *l)
{
	if (2 * l->err2 <= l->d.y)
	{
		l->err2 = l->d.x - l->err2;
		while (l->err2 < l->ed * l->w && (l->b.x != l->c.x || l->d.x < l->d.y))
		{
			l->c.x += l->s.x;
			plot(env, l->c.x, l->a.y, abs(l->err2) / l->ed - l->w + 1);
			if (l->d.x == 0)
				plot(env, l->a.x + (l->a.x - l->c.x), l->a.y
					, abs(l->err2) / l->ed - l->w + 1);
			l->err2 += l->d.y;
		}
		if (l->a.y == l->b.y)
			return (0);
		l->err += l->d.x;
		l->a.y += l->s.y;
	}
	return (1);
}

static void		draw_line(t_graph_env *env
		, t_vec2i a, t_vec2i b, float width)
{
	t_graph_aaline	l;

	l.a = a;
	l.b = b;
	l.w = (width + 1) / 2;
	l.d = ft_vec2i(ABS(b.x - a.x), ABS(b.y - a.y));
	l.s = ft_vec2i(a.x < b.x ? 1 : -1, a.y < b.y ? 1 : -1);
	l.err = l.d.x - l.d.y;
	l.ed = l.d.x + l.d.y == 0 ? 1 : sqrt(l.d.x * l.d.x + l.d.y * l.d.y);
	while (1)
	{
		plot(env, l.a.x, l.a.y, abs(l.err - l.d.x + l.d.y) / l.ed - l.w + 1);
		l.err2 = l.err;
		l.c.x = l.a.x;
		if (!step_x(env, &l) || !step_y(env, &l))
			break ;
	}
}

void			ft_graph_env_aaline(t_graph_env *env, t_vec2i a, t_vec2i b
		, float width)
{
	t_matrix	*mx;

	if (width < 1)
		width = 1;
	mx = (t_matrix*)ft_array_back(&env->matrices);
	a = ft_vec2i_transform(&a, mx);
	b = ft_vec2i_transform(&b, mx);
	draw_line(env, b, a, width);
}
