/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_insert.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 21:10:03 by paperrin          #+#    #+#             */
/*   Updated: 2017/12/02 18:33:31 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"
#include "internal_ft_vector.h"

char			*ft_vector_pinsert(t_vector *vector, char *place,
		char const *const elem)
{
	if (!ft_vector_reserve_it(vector, 1, &place))
		return (NULL);
	if (place <= vector->end && vector->end > vector->begin)
	{
		internal_ft_vector_copy_range(vector, place + vector->data_size, place,
				(vector->end - place) / vector->data_size + 1);
	}
	if (elem)
		ft_memmove(place, elem, vector->data_size);
	vector->end += vector->data_size;
	vector->reserve--;
	return (place);
}

char			*ft_vector_insert(t_vector *vector, size_t index,
		char const *const elem)
{
	return (ft_vector_pinsert(vector,
				vector->begin + index * vector->data_size, elem));
}

char			*ft_vector_push_front(t_vector *vector,
		char const *const elem)
{
	return (ft_vector_pinsert(
			vector,
			vector->begin,
			elem));
}

char			*ft_vector_push_back(t_vector *vector,
		char const *const elem)
{
	return (ft_vector_pinsert(
			vector,
			(vector->begin) ? vector->end + vector->data_size : NULL,
			elem));
}
