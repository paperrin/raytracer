/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_at.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 21:10:08 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/18 01:53:03 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"

void			*ft_vector_at(t_vector const *const vector, size_t index)
{
	return ((char*)vector->begin + index * vector->data_size);
}

void			*ft_vector_front(t_vector const *const vector)
{
	return (ft_vector_at(vector, 0));
}

void			*ft_vector_back(t_vector const *const vector)
{
	return (ft_vector_at(vector, ft_vector_size(vector) - 1));
}

void			*ft_vector_begin(t_vector const *const vector)
{
	return ((char*)vector->begin - vector->data_size);
}

void			*ft_vector_end(t_vector const *const vector)
{
	return ((char*)vector->end + vector->data_size);
}
