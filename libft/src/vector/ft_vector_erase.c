/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_erase.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 21:10:16 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/15 15:23:31 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"
#include "internal_ft_vector.h"

void			*ft_vector_perase_n(t_vector *vector, void *elem_first,
		size_t n)
{
	return (internal_ft_vector_perase_n_should_free(vector, elem_first, n, 1));
}

void			*ft_vector_erase_n(t_vector *vector, size_t index, size_t n)
{
	return (ft_vector_perase_n(vector,
				(char*)vector->begin + index * vector->data_size, n));
}

void			*ft_vector_perase(t_vector *vector, void *elem)
{
	return (ft_vector_perase_n(vector, elem, 1));
}

void			*ft_vector_erase(t_vector *vector, size_t index)
{
	return (ft_vector_perase(vector,
				(char*)vector->begin + index * vector->data_size));
}

void			ft_vector_clear(t_vector *vector)
{
	size_t		vector_size;

	vector_size = ft_vector_size(vector);
	internal_ft_vector_free_range(vector, vector->begin, vector_size);
	vector->reserve += vector_size;
	vector->end = (char*)vector->begin - vector->data_size;
}
