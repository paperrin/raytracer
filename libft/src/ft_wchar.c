/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wchar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 16:21:37 by paperrin          #+#    #+#             */
/*   Updated: 2017/12/05 14:49:18 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <wchar.h>

size_t			ft_wchar_len(wchar_t c)
{
	size_t		i;

	if (c < 0x80)
		return (1);
	i = 0;
	while (c != 0)
	{
		c >>= 1;
		i++;
	}
	i = i / 6 + (i % 6 > 0);
	return (i ? i : 1);
}

char			ft_wchar_char_at(wchar_t c, size_t index)
{
	const size_t		max_len = 4;
	size_t				size;
	char				mask;

	size = ft_wchar_len(c);
	mask = 0xF8;
	if (index >= size)
		return (-1);
	if (size == 1)
		return ((char)c);
	if (index == 0 && size > 1)
		mask = mask << (max_len - size);
	else
		mask = 0xC0;
	c >>= (size - index - 1) * 6;
	c &= (~mask);
	c |= mask << 1;
	return ((char)c);
}
