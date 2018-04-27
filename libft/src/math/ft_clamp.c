/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clamp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 01:24:38 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/27 18:28:01 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"

intmax_t		ft_min(intmax_t a, intmax_t b)
{
	return ((a < b) ? a : b);
}

intmax_t		ft_max(intmax_t a, intmax_t b)
{
	return ((a > b) ? a : b);
}

intmax_t		ft_clamp(intmax_t val, intmax_t min, intmax_t max)
{
	return (ft_max(ft_min(val, max), min));
}

intmax_t		ft_abs(intmax_t val)
{
	if (val < 0)
		return (-val);
	return (val);
}
