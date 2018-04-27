/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 19:07:09 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/27 13:09:56 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		f_map_free_str(void *str_ptr)
{
	ft_strdel((char**)str_ptr);
}

static int		f_map_cmp_str(void *a, void *b)
{
	if (*(char**)a == NULL)
		return (-1);
	if (*(char**)b == NULL)
		return (1);
	return (ft_strcmp(*(char**)a, *(char**)b));
}

t_map			scene_map_create(size_t val_size)
{
	t_map		map;

	map = ft_map_create(sizeof(char*), val_size);
	ft_map_free_key_val_set(&map, &f_map_free_str, NULL);
	ft_map_cmp_key_val_set(&map, &f_map_cmp_str, NULL);
	return (map);
}

void			*scene_map_add(t_map *const map,
		char const *const name)
{
	char		*name_cpy;
	void		*val;
	char		**key;

	if (scene_map_search(map, name))
		return (perror_string("could not add item, already exists"));
	name_cpy = NULL;
	if (name && !(name_cpy = ft_strdup(name)))
		return (perror_string(ERR_MEMORY));
	key = NULL;
	if (!ft_map_insert(map, (void**)&key, &val))
	{
		ft_strdel(&name_cpy);
		return (perror_string(ERR_MEMORY));
	}
	*key = name_cpy;
	return (val);
}
