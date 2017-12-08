/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_any.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 17:59:58 by paperrin          #+#    #+#             */
/*   Updated: 2017/08/02 19:28:29 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr_any(const char *s, const char *c)
{
	char	*p;

	p = (char*)s;
	while (*p)
	{
		if (ft_strchr(c, *p))
			return (p);
		p++;
	}
	if ((char)c[0] == '\0')
		return (p);
	return (NULL);
}
