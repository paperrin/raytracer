/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memrevcpy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 15:48:36 by paperrin          #+#    #+#             */
/*   Updated: 2017/12/05 14:38:33 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memrevcpy(void *dst, const void *src, size_t n)
{
	unsigned char			*d;
	const unsigned char		*s;

	if (n)
	{
		d = (unsigned char*)dst + n - 1;
		s = (unsigned char*)src + n - 1;
		while (n--)
			*(d--) = *(s--);
	}
	return (dst);
}
