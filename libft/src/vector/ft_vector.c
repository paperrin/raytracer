/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 21:07:04 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/15 15:01:18 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"

t_vector		ft_vector_create(size_t data_size,
		int (*f_copy)(void*, void*), void (*f_free)(void*))
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
	ft_memdel((void**)&vector->begin);
	ft_vector_create(vector->data_size, vector->f_copy, vector->f_free);
}
