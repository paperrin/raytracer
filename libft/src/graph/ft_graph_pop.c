/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_graph_pop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <paperrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 10:56:04 by paperrin          #+#    #+#             */
/*   Updated: 2017/10/04 10:58:20 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_graph.h"

void		ft_graph_pop(t_graph_env *env)
{
	if (env->matrices.size <= 1)
		return ;
	free(ft_array_pop_back(&env->matrices));
}
