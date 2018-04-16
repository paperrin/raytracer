/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_at.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 16:13:53 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/15 19:45:36 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_map.h"

void			*ft_map_at(t_map const *const map, void *key)
{
	int			index;

	if ((index = ft_map_index_at(map, key)) < 0)
		return (NULL);
	return (ft_vector_at(&map->v_keys, index));
}

int				ft_map_index_at(t_map const *const map, void *key)
{
	int			i;
	size_t		size;

	if (!key || !map->v_keys.f_cmp)
		return (-1);
	size = ft_vector_size(&map->v_keys);
	i = -1;
	while (++i < (int)size)
	{
		if ((*map->v_keys.f_cmp)(key, ft_vector_at(&map->v_keys, i)) == 0)
			return (i);
	}
	return (-1);
}
