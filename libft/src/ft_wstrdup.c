/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wstrdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/26 19:42:54 by paperrin          #+#    #+#             */
/*   Updated: 2016/11/28 13:58:57 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <wchar.h>

wchar_t		*ft_wstrdup(const wchar_t *s1)
{
	wchar_t		*dst;

	dst = (wchar_t*)malloc(sizeof(wchar_t) * ft_wstrlen(s1) + 1);
	if (dst)
		dst = ft_wstrcpy(dst, s1);
	return (dst);
}
