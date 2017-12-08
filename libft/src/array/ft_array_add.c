/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_add.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <paperrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 02:46:12 by paperrin          #+#    #+#             */
/*   Updated: 2017/09/29 17:30:25 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_array.h"

static void			shift_right(t_array *array, size_t index)
{
	size_t		i;

	i = array->size;
	while (--i >= index)
		array->begin[i + 1] = array->begin[i];
}

t_array_it			ft_array_add(t_array *array, size_t index, void *data)
{
	if (index > array->size)
		return (NULL);
	if (!ft_array_reserve(array, index == 0, index != 0))
		return (NULL);
	if (index == 0)
	{
		array->begin--;
		array->reserve_front--;
	}
	else
	{
		if (index != array->size)
			shift_right(array, index);
		array->end++;
		array->reserve_back--;
	}
	array->size++;
	array->begin[index] = data;
	return (array->begin);
}
