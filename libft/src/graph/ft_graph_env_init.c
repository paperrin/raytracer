/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_graph_env_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <paperrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 10:20:04 by paperrin          #+#    #+#             */
/*   Updated: 2017/10/19 17:08:07 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_graph.h"

int				ft_graph_env_init(t_graph_env **env
	, void (*f_put_pixel)(t_vec3f pos, t_color_rgb color, void *param)
	, void (*f_put_pixel_rgba)(t_vec3f pos, t_color_rgba color, void *param)
	, void *put_pixel_param)
{
	t_matrix	*mx;

	if (*env)
	{
		while ((*env)->matrices.size)
			free(ft_array_pop_back(&(*env)->matrices));
		ft_array_free(&(*env)->matrices);
		free(*env);
		*env = NULL;
	}
	if (!(*env = (t_graph_env*)malloc(sizeof(t_graph_env))))
		return (0);
	(*env)->f_put_pixel = f_put_pixel;
	(*env)->f_put_pixel_rgba = f_put_pixel_rgba;
	(*env)->put_pixel_param = put_pixel_param;
	(*env)->matrices = ft_array_init(NULL);
	(*env)->fill_rgba = ft_color_rgba(255, 255, 255, 1);
	if (!ft_array_reserve(&(*env)->matrices, 0, 10))
		return (0);
	if (!(mx = ft_matrix_new()))
		return (0);
	ft_matrix_to_identity(mx);
	ft_array_push_back(&(*env)->matrices, mx);
	return (1);
}
