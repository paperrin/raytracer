/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 13:48:24 by paperrin          #+#    #+#             */
/*   Updated: 2017/12/06 19:45:34 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <math.h>

static size_t		count_decimal_zeros(const char *str)
{
	size_t		i;

	i = 0;
	while (str[i] == '0')
		i++;
	return (i);
}

long double			ft_atof(const char *str, char sep)
{
	int			i_part;
	int			d_part;
	char		*decimal;
	long double	ret;

	i_part = ft_atoi(str);
	if (!(decimal = ft_strchr(str, sep)))
		return (i_part);
	d_part = ft_atoi(&decimal[1]);
	ret = (long double)i_part
		+ (long double)d_part / pow(10, ((int)floor(log10(d_part)))
				+ 1 + count_decimal_zeros(&decimal[1]));
	return (ret);
}
