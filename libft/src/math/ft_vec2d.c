/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec2d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 13:58:35 by paperrin          #+#    #+#             */
/*   Updated: 2017/12/05 14:58:31 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"
#include <stdlib.h>

t_vec2d			ft_vec2d(double x, double y)
{
	t_vec2d		ret;

	ret.x = x;
	ret.y = y;
	return (ret);
}

t_vec2d			*ft_vec2d_new(double x, double y)
{
	t_vec2d		*ret;

	ret = (t_vec2d*)malloc(sizeof(t_vec2d));
	if (ret)
		*ret = ft_vec2d(x, y);
	return (ret);
}
