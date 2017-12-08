/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_graph_poly_fill.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <paperrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 22:33:08 by paperrin          #+#    #+#             */
/*   Updated: 2017/10/07 03:43:57 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_graph.h"
#include <stdio.h>

static int		x_smaller(void *a, void *b)
{
	return (((t_edge*)a)->x <= ((t_edge*)b)->x);
}

static void		manage_active_list(t_array *edges, t_array *active, int y)
{
	void		*removed;
	int			i;
	int			j;

	i = (int)active->size;
	while (--i >= 0)
	{
		if (((t_edge*)active->begin[i])->y_max == y)
		{
			removed = ft_array_pop(active, i);
			j = (int)edges->size;
			while (--j >= 0)
				if (removed == edges->begin[j])
					free(ft_array_pop(edges, j));
		}
	}
	i = (int)edges->size;
	while (--i >= 0)
		if (((t_edge*)edges->begin[i])->y_min == y)
			ft_array_push_back(active, edges->begin[i]);
	ft_array_sort(active, &x_smaller);
}

static void		fill_line(t_edge **pair, int y
	, void (*f_put_pixel)(t_vec3f pos, t_color_rgb color, void *param)
	, void *param)
{
	int				x;

	x = pair[0]->x;
	while (x < pair[1]->x)
	{
		(*f_put_pixel)(ft_vec3f(x, y, 0)
			, ft_color_interpolate(pair[0]->color, pair[1]->color
				, (float)(x - pair[0]->x) / (pair[1]->x - pair[0]->x))
			, param);
		x++;
	}
}

static void		increment_x(t_array *active, int y)
{
	t_edge	*edge;
	int		i;

	i = -1;
	while (++i < (int)active->size)
	{
		edge = active->begin[i];
		edge->sum += (float)edge->dx / edge->dy;
		edge->color = ft_color_interpolate(edge->color_min, edge->color_max
			, (float)(y - edge->y_min) / edge->dy);
		while (edge->sum >= 1)
		{
			edge->x += edge->sign;
			edge->sum -= 1;
		}
	}
}

int				ft_graph_poly_fill(t_array *edges
	, void (*f_put_pixel)(t_vec3f pos, t_color_rgb color, void *param)
	, void *param)
{
	t_array		active;
	int			y;
	int			i;

	active = ft_array_init(NULL);
	if (!edges || !ft_array_reserve(&active, 0, edges->size))
		return (0);
	y = ((t_edge*)edges->begin[0])->y_min;
	while (edges->size)
	{
		manage_active_list(edges, &active, y);
		i = 0;
		while (i < (int)active.size)
		{
			fill_line((t_edge**)&active.begin[i], y, f_put_pixel, param);
			i += 2;
		}
		y++;
		increment_x(&active, y);
	}
	ft_array_free(edges);
	free(edges);
	ft_array_free(&active);
	return (1);
}
