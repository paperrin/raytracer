/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_map_search.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 19:42:26 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/15 19:43:37 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			*scene_map_search(t_map const *const map,
		char const *const name)
{
	if (!name)
		return (NULL);
	return (ft_map_at(map, (void*)&name));
}

int				scene_map_search_index(t_map const *const map,
		char const *const name)
{
	if (!name)
		return (-1);
	return (ft_map_index_at(map, (void*)&name));
}
