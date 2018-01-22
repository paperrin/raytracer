/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 15:11:40 by paperrin          #+#    #+#             */
/*   Updated: 2018/01/21 21:44:29 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dst;

	dst = ft_strnew(ft_strlen(s1));
	if (dst)
		dst = ft_strcpy(dst, s1);
	return (dst);
}

char	*ft_strdupw(const wchar_t *ws)
{
	char	*dst;
	int		i;
	int		j;
	int		pos;
	char	c;

	dst = ft_strnew(ft_wstrlen_char(ws) + 1);
	if (!dst)
		return (NULL);
	i = -1;
	pos = 0;
	while (ws[++i])
	{
		j = -1;
		while ((c = ft_wchar_char_at(ws[i], ++j)) != -1)
			dst[pos++] = c;
	}
	dst[pos] = '\0';
	return (dst);
}
