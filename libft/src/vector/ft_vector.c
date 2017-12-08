/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 21:07:04 by paperrin          #+#    #+#             */
/*   Updated: 2017/12/01 18:33:10 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"

t_vector		ft_vector_create(size_t data_size,
		int (*f_copy)(char*, char*), void (*f_free)(char*))
{
	t_vector		vector;

	vector.begin = NULL;
	vector.end = NULL;
	vector.reserve = 0;
	vector.data_size = data_size;
	vector.f_free = f_free;
	vector.f_copy = f_copy;
	return (vector);
}

void			ft_vector_destroy(t_vector *vector)
{
	ft_vector_clear(vector);
	free(vector->begin);
	ft_vector_create(vector->data_size, vector->f_copy, vector->f_free);
}
