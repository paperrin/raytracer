/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 14:35:12 by paperrin          #+#    #+#             */
/*   Updated: 2016/12/14 18:34:44 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char *dst;

	dst = (char*)malloc(sizeof(char) * n + 1);
	if (dst)
	{
		dst = ft_strncpy(dst, s1, n);
		dst[n] = '\0';
	}
	return (dst);
}

char	*ft_strdupw_nchar(const wchar_t *ws, size_t n)
{
	char	*dst;
	int		i;
	int		j;
	size_t	pos;
	char	c;

	n = ft_wstrnlen_char(ws, n);
	dst = ft_strnew(n);
	if (!dst)
		return (NULL);
	i = -1;
	pos = 0;
	while (ws[++i] && pos < n)
	{
		j = -1;
		while ((c = ft_wchar_char_at(ws[i], ++j)) != -1 && pos < n)
			dst[pos++] = c;
	}
	dst[pos] = '\0';
	return (dst);
}
