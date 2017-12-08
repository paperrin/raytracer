/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_pop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <paperrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 04:14:49 by paperrin          #+#    #+#             */
/*   Updated: 2017/09/29 17:30:28 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_array.h"

static void			shift_left(t_array *array, size_t index)
{
	while (index < array->size - 1)
	{
		array->begin[index] = array->begin[index + 1];
		index++;
	}
}

void				*ft_array_pop(t_array *array, size_t index)
{
	void	*elem;

	if (index >= array->size || !array->data)
		return (NULL);
	elem = array->begin[index];
	if (index == 0)
	{
		array->reserve_front++;
		array->begin++;
	}
	else
	{
		if (index != array->size - 1)
			shift_left(array, index);
		array->reserve_back++;
		array->end--;
	}
	array->size--;
	return (elem);
}
