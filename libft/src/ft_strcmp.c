/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 14:55:07 by paperrin          #+#    #+#             */
/*   Updated: 2017/08/06 00:14:17 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	unsigned char *a;
	unsigned char *b;

	a = (unsigned char*)s1;
	b = (unsigned char*)s2;
	while (*a && *a == *b)
	{
		a++;
		b++;
	}
	return (*a - *b);
}
