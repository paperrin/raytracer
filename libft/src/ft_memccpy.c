/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 21:41:39 by paperrin          #+#    #+#             */
/*   Updated: 2017/07/29 15:25:53 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char			*d;
	const unsigned char		*s;

	d = dst;
	s = src;
	while (n--)
	{
		if ((*(d++) = *(s++)) == (unsigned char)c)
			return (d);
	}
	return (NULL);
}
