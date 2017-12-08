/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 13:45:09 by paperrin          #+#    #+#             */
/*   Updated: 2017/08/06 00:10:48 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char *a;
	unsigned char *b;

	a = (unsigned char*)s1;
	b = (unsigned char*)s2;
	while (n--)
	{
		if (*a != *b)
			return (*a - *b);
		a++;
		b++;
	}
	return (0);
}
