/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wstrjoin_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/26 19:46:43 by paperrin          #+#    #+#             */
/*   Updated: 2016/11/26 19:50:18 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <wchar.h>

wchar_t		*ft_wstrjoin_free(wchar_t **a, wchar_t **b, int free)
{
	wchar_t	*str;

	str = ft_wstrjoin(*a, *b);
	if (free == 2 || free == 0)
		ft_memdel((void**)a);
	if (free == 2 || free == 1)
		ft_memdel((void**)b);
	return (str);
}
