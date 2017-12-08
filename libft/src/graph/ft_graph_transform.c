/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_graph_transform.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <paperrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 10:33:00 by paperrin          #+#    #+#             */
/*   Updated: 2017/10/12 12:40:39 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_graph.h"

void			ft_graph_translate(t_graph_env *env, float x, float y, float z)
{
	ft_matrix_translate(ft_array_back(&env->matrices), x, y, z);
}

void			ft_graph_scale(t_graph_env *env, float x, float y, float z)
{
	ft_matrix_scale(ft_array_back(&env->matrices), x, y, z);
}

void			ft_graph_rot_x(t_graph_env *env, float alpha)
{
	ft_matrix_rot_x(ft_array_back(&env->matrices), alpha);
}

void			ft_graph_rot_y(t_graph_env *env, float alpha)
{
	ft_matrix_rot_y(ft_array_back(&env->matrices), alpha);
}

void			ft_graph_rot_z(t_graph_env *env, float alpha)
{
	ft_matrix_rot_z(ft_array_back(&env->matrices), alpha);
}
