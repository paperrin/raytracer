/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_info.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 22:10:02 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/20 22:32:52 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"

size_t				ft_vector_size(t_vector const *const vector)
{
	if (!vector->begin)
		return (0);
	return (((char*)vector->end - (char*)vector->begin)
			/ vector->data_size) + 1;
}

size_t				ft_vector_size_bytes(t_vector const *const vector)
{
	if (!vector->begin)
		return (0);
	return ((char*)vector->end - (char*)vector->begin + vector->data_size);
}

size_t				ft_vector_capacity(t_vector const *const vector)
{
	return (ft_vector_size(vector) + vector->reserve);
}

size_t				ft_vector_capacity_bytes(t_vector const *const vector)
{
	return (ft_vector_capacity(vector) * vector->data_size);
}

int					ft_vector_empty(t_vector const *const vector)
{
	return (!vector->begin || vector->end < vector->begin);
}
