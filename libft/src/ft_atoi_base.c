/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 18:26:42 by paperrin          #+#    #+#             */
/*   Updated: 2017/08/06 00:04:24 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
			|| c == '\v' || c == '\f' || c == '\r');
}

static int		is_char_in_base(char c, int base)
{
	if (base >= 2 && base <= 10)
		return (c >= '0' && c <= '1' + base - 1);
	else if (base > 10 && base <= 36)
		return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'a' + base - 11));
	return (0);
}

int				ft_atoi_base(const char *str, int base)
{
	char	*p;
	int		mult;
	int		ret;

	p = (char*)str;
	while (is_whitespace(*p))
		p++;
	mult = 1;
	if (base == 10 && (*p == '-' || *p == '+'))
	{
		if (*p == '-')
			mult = -1;
		p++;
	}
	ret = 0;
	while (is_char_in_base(ft_tolower(*p), base))
	{
		ret *= base;
		ret += (*p > '9') ? (ft_tolower(*p) - 'a' + 10) : (*p - '0');
		p++;
	}
	ret *= mult;
	return (ret);
}
