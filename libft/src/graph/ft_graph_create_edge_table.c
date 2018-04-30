/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_graph_create_edge_table.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <paperrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 20:56:34 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/27 18:31:34 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_graph.h"

static t_edge	*create_edge(t_vec3f *va, t_color_rgb *ca
	, t_vec3f *vb, t_color_rgb *cb)
{
	t_edge	*edge;

	if (!(edge = (t_edge*)malloc(sizeof(t_edge))))
		return (NULL);
	if (va->y > vb->y)
	{
		ft_swap((void**)&va, (void**)&vb);
		ft_swap((void**)&ca, (void**)&cb);
	}
	edge->y_max = roundf(vb->y);
	edge->y_min = roundf(va->y);
	edge->x = va->x;
	edge->color_max = *cb;
	edge->color_min = *ca;
	edge->color = *ca;
	edge->sign = (vb->x > va->x ? 1 : -1);
	edge->dx = ft_absf(va->x - vb->x);
	edge->dy = ft_absf(va->y - vb->y);
	edge->sum = 0;
	return (edge);
}

static int		create_edge_table(t_array *edges, t_vec3f *vertices
	, t_color_rgb *colors, size_t n)
{
	t_edge		*new_edge;
	int			i;

	*edges = ft_array_init(NULL);
	if (n < 3 || !ft_array_reserve(edges, 0, n))
		return (0);
	if (vertices[n - 1].y != vertices[0].y)
	{
		if (!(new_edge = create_edge(&vertices[n - 1], &colors[n - 1]
			, &vertices[0], &colors[0]))
				|| !ft_array_push_back(edges, new_edge))
			return (0);
	}
	i = -1;
	while (++i < (int)n - 1)
	{
		if (vertices[i].y == vertices[i + 1].y)
			continue ;
		if (!(new_edge = create_edge(&vertices[i], &colors[i]
				, &vertices[i + 1], &colors[i + 1])))
			return (0);
		if (!ft_array_push_back(edges, new_edge))
			return (0);
	}
	return (1);
}

static int		y_min_smaller(void *a, void *b)
{
	return (((t_edge*)a)->y_min <= ((t_edge*)b)->y_min);
}

t_array			*ft_graph_create_edge_table(t_vec3f *vertices,
		t_color_rgb *colors, size_t n)
{
	t_array		*edges;

	if (!(edges = (t_array*)malloc(sizeof(t_array))))
		return (NULL);
	if (!create_edge_table(edges, vertices, colors, n))
		return (NULL);
	if (!ft_array_sort(edges, &y_min_smaller))
		return (NULL);
	return (edges);
}
