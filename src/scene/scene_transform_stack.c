/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_transform_stack.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 01:27:17 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/20 22:46:29 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		scene_transform_push(t_scene *const scene)
{
	t_matrix		*mx;
	t_matrix		*mx_r;

	if (!(mx = (t_matrix*)ft_vector_push_back(&scene->v_mx, NULL)))
		return (error_string(ERR_MEMORY));
	if (!(mx_r = (t_matrix*)ft_vector_push_back(&scene->v_mx_r, NULL)))
	{
		ft_vector_pop_back(&scene->v_mx, NULL);
		return (error_string(ERR_MEMORY));
	}
	*mx = scene->mx;
	*mx_r = scene->mx_r;
	return (1);
}

void	scene_transform_pop(t_scene *const scene)
{
	ft_vector_pop_back(&scene->v_mx, NULL);
	ft_vector_pop_back(&scene->v_mx_r, NULL);
	if (ft_vector_empty(&scene->v_mx))
	{
		ft_matrix_to_identity(&scene->mx);
		ft_matrix_to_identity(&scene->mx_r);
	}
	else
	{
		scene->mx = *(t_matrix*)ft_vector_back(&scene->v_mx);
		scene->mx_r = *(t_matrix*)ft_vector_back(&scene->v_mx_r);
	}
}
