/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_insert.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 16:08:56 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/15 18:44:14 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_map.h"

int				ft_map_insert(t_map *const map,
		void **ret_key, void **ret_val)
{
	if (!(*ret_key = ft_vector_push_back(&map->v_keys, NULL)))
		return (0);
	if (!(*ret_val = ft_vector_push_back(&map->v_values, NULL)))
	{
		ft_vector_pop_back(&map->v_keys, NULL);
		*ret_key = NULL;
		return (0);
	}
	return (1);
}
