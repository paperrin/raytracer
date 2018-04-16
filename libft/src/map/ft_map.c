/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 14:52:09 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/15 17:35:48 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_map.h"

t_map			ft_map_create(size_t key_size, size_t val_size)
{
	t_map		map;

	map.v_keys = ft_vector_create(key_size, NULL, NULL);
	map.v_values = ft_vector_create(val_size, NULL, NULL);
	return (map);
}

void			ft_map_cmp_key_val_set(t_map *const map,
		int (*f_cmp_key)(void*, void*), int (*f_cmp_val)(void*, void*))
{
	map->v_keys.f_cmp = f_cmp_key;
	map->v_values.f_cmp = f_cmp_val;
}

void			ft_map_free_key_val_set(t_map *const map,
		void (*f_free_key)(void*), void (*f_free_val)(void*))
{
	map->v_keys.f_free = f_free_key;
	map->v_values.f_free = f_free_val;
}

void			ft_map_destroy(t_map *const map)
{
	ft_vector_destroy(&map->v_keys);
	ft_vector_destroy(&map->v_values);
}

size_t			ft_map_size(t_map const *const map)
{
	return (ft_vector_size(&map->v_keys));
}
