/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr_any.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 23:49:17 by paperrin          #+#    #+#             */
/*   Updated: 2018/01/21 23:49:33 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr_any(void const *const s, size_t n,
		void const *const to_search, size_t n_to_search)
{
	unsigned char		*p;

	p = (unsigned char*)s;
	while (n--)
	{
		if (ft_memchr(to_search, *p, n_to_search))
			return (p);
		p++;
	}
	return (NULL);
}
