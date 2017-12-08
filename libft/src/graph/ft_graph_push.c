/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_graph_push.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <paperrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 10:52:02 by paperrin          #+#    #+#             */
/*   Updated: 2017/10/04 11:35:31 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_graph.h"

int				ft_graph_push(t_graph_env *env)
{
	t_matrix		*mx;

	if (!(mx = ft_matrix_new()))
		return (0);
	ft_matrix_copy(mx, ft_array_back(&env->matrices));
	if (!ft_array_push_back(&env->matrices, mx))
		return (0);
	return (1);
}
