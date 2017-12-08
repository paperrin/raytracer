/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lerp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <paperrin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 17:12:05 by paperrin          #+#    #+#             */
/*   Updated: 2017/10/11 17:14:32 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

intmax_t	ft_lerp(intmax_t val, intmax_t min, intmax_t max)
{
	if (val > max)
		val = max;
	else if (val < min)
		val = min;
	return (val);
}
