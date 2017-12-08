/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <paperrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 22:37:34 by paperrin          #+#    #+#             */
/*   Updated: 2017/12/05 15:23:32 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_array.h"

t_array				ft_array_init(void (*f_free)(void**))
{
	t_array		array;

	array.data = NULL;
	array.begin = NULL;
	array.end = NULL;
	array.f_free = f_free;
	array.size = 0;
	array.reserve_front = 0;
	array.reserve_back = 0;
	return (array);
}
