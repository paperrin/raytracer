/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_resize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 21:09:59 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/19 01:29:56 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"

void			*ft_vector_reserve(t_vector *vector, size_t reserve)
{
	void		*new_begin;
	size_t		new_capacity;
	size_t		size_byte;

	reserve = ft_max(reserve, vector->reserve);
	if (reserve <= vector->reserve)
		return (vector->begin);
	new_capacity = ft_vector_size(vector) + reserve;
	if (!(new_begin = (void*)malloc(vector->data_size * new_capacity)))
		return (NULL);
	size_byte = ft_vector_size_bytes(vector);
	ft_memmove(new_begin, vector->begin, size_byte);
	free(vector->begin);
	vector->begin = new_begin;
	vector->end = (char*)new_begin + size_byte - vector->data_size;
	vector->reserve = reserve;
	return (vector->begin);
}

void			*ft_vector_reserve_it(t_vector *vector, size_t reserve,
		void **it)
{
	size_t		it_offset;

	if (reserve > vector->reserve)
	{
		it_offset = (char*)*it - (char*)vector->begin;
		if (!ft_vector_reserve(vector, reserve))
			return (NULL);
		*it = it_offset + (char*)vector->begin;
	}
	return (vector->begin);
}

void			*ft_vector_shrink_to_fit(t_vector *vector)
{
	void		*new_begin;
	size_t		size_byte;

	if (!vector->reserve)
		return (vector->begin);
	size_byte = ft_vector_size_bytes(vector);
	if (!(new_begin = (void*)malloc(size_byte)))
		return (NULL);
	ft_memmove(new_begin, vector->begin, size_byte);
	vector->begin = new_begin;
	vector->end = (char*)new_begin + size_byte - vector->data_size;
	vector->reserve = 0;
	return (vector->begin);
}
