/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 12:24:18 by paperrin          #+#    #+#             */
/*   Updated: 2018/01/21 23:49:08 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char		*p;

	p = (unsigned char*)s;
	while (n--)
	{
		if (*p == (unsigned char)c)
			return (p);
		p++;
	}
	return (NULL);
}
