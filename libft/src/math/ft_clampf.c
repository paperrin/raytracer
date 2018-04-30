/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clampf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 01:18:47 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/27 18:28:47 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"

long double		ft_minf(long double a, long double b)
{
	return ((a < b) ? a : b);
}

long double		ft_maxf(long double a, long double b)
{
	return ((a > b) ? a : b);
}

long double		ft_clampf(long double val, long double min, long double max)
{
	return (ft_maxf(ft_minf(val, max), min));
}

long double		ft_absf(long double val)
{
	if (val < 0)
		return (-val);
	return (val);
}
