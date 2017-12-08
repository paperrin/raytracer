/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 15:02:18 by paperrin          #+#    #+#             */
/*   Updated: 2017/12/06 13:56:03 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
			|| c == '\v' || c == '\f' || c == '\r');
}

int				ft_atoi(const char *str)
{
	char	*p;
	int		mult;
	int		ret;

	p = (char*)str;
	while (is_whitespace(*p))
		p++;
	mult = 1;
	if (*p == '-' || *p == '+')
	{
		if (*p == '-')
			mult = -1;
		p++;
	}
	ret = 0;
	while (*p >= '0' && *p <= '9')
	{
		ret *= 10;
		ret += *p - '0';
		p++;
	}
	ret *= mult;
	return (ret);
}
