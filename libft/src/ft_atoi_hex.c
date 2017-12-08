/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_hex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/05 23:17:26 by paperrin          #+#    #+#             */
/*   Updated: 2017/08/06 00:15:41 by paperrin         ###   ########.fr       */
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

int				ft_atoi_hex_is_valid(const char *str)
{
	char	*p;

	p = (char*)str;
	while (is_whitespace(*p))
		p++;
	if (p[0] && p[1] && !ft_strncmp(p, "0x", 2) && is_char_in_base(p[2], 16))
		return (p - str + 2);
	return (0);
}

int				ft_atoi_hex(const char *str)
{
	int		index;

	index = ft_atoi_hex_is_valid(str);
	if (index)
		return (ft_atoi_base(str + index, 16));
	return (0);
}
