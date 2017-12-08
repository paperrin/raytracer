/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_pop_at.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 21:10:12 by paperrin          #+#    #+#             */
/*   Updated: 2017/12/01 22:21:29 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"
#include "internal_ft_vector.h"

char			*ft_vector_pop_at(t_vector *vector, size_t index,
		char *ret_value)
{
	char		*to_pop;

	to_pop = vector->begin + index * vector->data_size;
	ft_memmove(ret_value, to_pop, vector->data_size);
	return (internal_ft_vector_perase_n_should_free(vector, to_pop, 1, 0));
}

char			*ft_vector_pop_front(t_vector *vector, char *ret_value)
{
	ft_memmove(ret_value, vector->begin, vector->data_size);
	return (internal_ft_vector_perase_n_should_free(vector,
				vector->begin, 1, 0));
}

char			*ft_vector_pop_back(t_vector *vector, char *ret_value)
{
	ft_memmove(ret_value, vector->end, vector->data_size);
	return (internal_ft_vector_perase_n_should_free(vector,
				vector->end, 1, 0));
}
