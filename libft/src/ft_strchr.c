/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 10:24:31 by paperrin          #+#    #+#             */
/*   Updated: 2017/08/02 19:27:46 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*p;

	p = (char*)s;
	while (*p)
	{
		if (*p == (char)c)
			return (p);
		p++;
	}
	if ((char)c == '\0')
		return (p);
	return (NULL);
}
