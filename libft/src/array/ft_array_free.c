/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <paperrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 16:55:23 by paperrin          #+#    #+#             */
/*   Updated: 2017/12/05 15:27:09 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_array.h"

void				ft_array_free(t_array *array)
{
	if (array->data)
		free(array->data);
	array->data = NULL;
	array->begin = NULL;
	array->end = NULL;
	array->f_free = NULL;
	array->size = 0;
	array->reserve_front = 0;
	array->reserve_back = 0;
}
