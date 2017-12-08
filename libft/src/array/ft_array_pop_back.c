/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_pop_back.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <paperrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 16:48:20 by paperrin          #+#    #+#             */
/*   Updated: 2017/09/29 17:30:32 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_array.h"

void				*ft_array_pop_back(t_array *array)
{
	return (ft_array_pop(array, array->size - 1));
}
