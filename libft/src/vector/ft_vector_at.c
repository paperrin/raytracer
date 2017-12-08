/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_at.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 21:10:08 by paperrin          #+#    #+#             */
/*   Updated: 2017/12/01 19:58:24 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vector.h"

char			*ft_vector_at(t_vector const *const vector, size_t index)
{
	return (vector->begin + index * vector->data_size);
}

char			*ft_vector_begin(t_vector const *const vector)
{
	return (vector->begin - vector->data_size);
}

char			*ft_vector_end(t_vector const *const vector)
{
	return (vector->end + vector->data_size);
}
