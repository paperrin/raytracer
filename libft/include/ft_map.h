/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 15:28:38 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/18 03:32:12 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MAP_H
# define FT_MAP_H

# include "ft_vector.h"

typedef struct	s_map_pair
{
	void				*key;
	void				*val;
}				t_map_pair;

typedef struct	s_map
{
	t_vector			v_keys;
	t_vector			v_values;
}				t_map;

t_map			ft_map_create(size_t key_size, size_t val_size);
void			ft_map_cmp_key_val_set(t_map *const map,
		int (*f_cmp_key)(void*, void*), int (*f_cmp_val)(void*, void*));
void			ft_map_free_key_val_set(t_map *const map,
		void (*f_free_key)(void*), void (*f_free_val)(void*));
void			ft_map_destroy(t_map *const map);

int				ft_map_insert(t_map *const map,
		void **ret_key, void **ret_val);

int				ft_map_index_at(t_map const *const map, void *key);
void			*ft_map_at(t_map const *const map, void *key);

size_t			ft_map_size(t_map const *const map);

#endif
