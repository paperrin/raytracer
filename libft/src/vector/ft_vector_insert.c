/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_insert.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 21:10:03 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/15 15:22:23 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"
#include "internal_ft_vector.h"

void			*ft_vector_pinsert(t_vector *vector, void *place,
		void const *const elem)
{
	if (!ft_vector_reserve_it(vector, 1, &place))
		return (NULL);
	if (place <= vector->end && vector->end > vector->begin)
	{
		internal_ft_vector_copy_range(vector, (char*)place + vector->data_size,
				place, ((char*)vector->end - (char*)place)
						/ vector->data_size + 1);
	}
	if (elem)
		ft_memmove(place, elem, vector->data_size);
	vector->end = (char*)vector->end + vector->data_size;
	vector->reserve--;
	return (place);
}

void			*ft_vector_insert(t_vector *vector, size_t index,
		void const *const elem)
{
	return (ft_vector_pinsert(vector,
				(char*)vector->begin + index * vector->data_size, elem));
}

void			*ft_vector_push_front(t_vector *vector,
		void const *const elem)
{
	return (ft_vector_pinsert(
			vector,
			vector->begin,
			elem));
}

void			*ft_vector_push_back(t_vector *vector,
		void const *const elem)
{
	return (ft_vector_pinsert(
			vector,
			(vector->begin) ? (char*)vector->end + vector->data_size : NULL,
			elem));
}
