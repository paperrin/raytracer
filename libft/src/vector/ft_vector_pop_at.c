/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_pop_at.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 21:10:12 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/20 22:39:57 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"
#include "internal_ft_vector.h"

void			*ft_vector_pop_at(t_vector *vector, size_t index,
		void *ret_value)
{
	void		*to_pop;

	to_pop = (char*)vector->begin + index * vector->data_size;
	if (to_pop < vector->begin || to_pop > vector->end)
		return (NULL);
	if (ret_value)
		ft_memmove(ret_value, to_pop, vector->data_size);
	return (internal_ft_vector_perase_n_should_free(vector, to_pop, 1, 0));
}

void			*ft_vector_pop_front(t_vector *vector, void *ret_value)
{
	if (ft_vector_empty(vector))
		return (NULL);
	return (ft_vector_pop_at(vector, 0, ret_value));
}

void			*ft_vector_pop_back(t_vector *vector, void *ret_value)
{
	int		size;

	size = ft_vector_size(vector);
	if (!size)
		return (NULL);
	return (ft_vector_pop_at(vector, size - 1, ret_value));
}
