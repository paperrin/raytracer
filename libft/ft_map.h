/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 22:50:11 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/14 22:56:57 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MAP_H
# define FT_MAP_H

# include "ft_vector.h"

t_vector		ft_vector_create(size_t data_size, int (*f_copy)(char*, char*),
		void (*f_free)(char*));
void			ft_vector_destroy(t_vector *vector);

size_t			ft_vector_size(t_vector const *const vector);

char			*ft_vector_push_back(t_vector *vector,
		char const *const elem);

#endif
