/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memrealloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 21:48:42 by paperrin          #+#    #+#             */
/*   Updated: 2018/01/22 01:07:13 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void		*ft_memrealloc_offset(void **src, size_t src_size, size_t new_size,
		size_t offset)
{
	void		*new;
	size_t		n_copy;

	if (!src)
		return (NULL);
	if ((new = (void*)malloc(sizeof(unsigned char) * new_size)))
	{
		if (*src && offset < src_size)
		{
			n_copy = 0;
			if ((long)src_size - offset > 0)
				n_copy = src_size - offset;
			if (n_copy > new_size)
				n_copy = new_size;
			ft_memcpy(new, &(*(char*)src[offset]), n_copy);
		}
		free(*src);
		*src = new;
	}
	else
		ft_memdel(src);
	return (new);
}

void		*ft_memrealloc(void **src, size_t src_size, size_t new_size)
{
	return (ft_memrealloc_offset(src, src_size, new_size, 0));
}
