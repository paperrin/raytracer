/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wstrjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/26 19:40:55 by paperrin          #+#    #+#             */
/*   Updated: 2016/11/26 19:46:24 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <wchar.h>

wchar_t		*ft_wstrjoin(wchar_t const *s1, wchar_t const *s2)
{
	wchar_t	*ret;
	size_t	s1_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_wstrlen(s1);
	ret = (wchar_t*)malloc(sizeof(wchar_t) * (s1_len + ft_wstrlen(s2) + 1));
	if (ret)
	{
		ret = ft_wstrcpy(ret, s1);
		ft_wstrcpy(ret + s1_len, s2);
	}
	return (ret);
}
