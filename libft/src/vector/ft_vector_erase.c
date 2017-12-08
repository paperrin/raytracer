/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_erase.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 21:10:16 by paperrin          #+#    #+#             */
/*   Updated: 2017/12/01 22:21:46 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"
#include "internal_ft_vector.h"

char			*ft_vector_perase_n(t_vector *vector, char *elem_first,
		size_t n)
{
	return (internal_ft_vector_perase_n_should_free(vector, elem_first, n, 1));
}

char			*ft_vector_erase_n(t_vector *vector, size_t index, size_t n)
{
	return (ft_vector_perase_n(vector,
				vector->begin + index * vector->data_size, n));
}

char			*ft_vector_perase(t_vector *vector, char *elem)
{
	return (ft_vector_perase_n(vector, elem, 1));
}

char			*ft_vector_erase(t_vector *vector, size_t index)
{
	return (ft_vector_perase(vector,
				vector->begin + index * vector->data_size));
}

void			ft_vector_clear(t_vector *vector)
{
	size_t		vector_size;

	vector_size = ft_vector_size(vector);
	internal_ft_vector_free_range(vector, vector->begin, vector_size);
	vector->reserve += vector_size;
	vector->end = vector->begin - vector->data_size;
}
