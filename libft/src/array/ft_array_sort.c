/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <paperrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 21:30:37 by paperrin          #+#    #+#             */
/*   Updated: 2017/11/10 23:35:18 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_array.h"

t_array_it			ft_array_sort(t_array *array, int (*f_cmp)(void*, void*))
{
	int		sorted;
	int		i;

	if (!array->data)
		return (NULL);
	sorted = 0;
	while (!sorted)
	{
		sorted = 1;
		i = -1;
		while (++i < (int)array->size - 1)
		{
			if (!f_cmp(array->begin[i], array->begin[i + 1]))
			{
				sorted = 0;
				ft_swap(&array->begin[i], &array->begin[i + 1]);
			}
		}
	}
	return (array->begin);
}
