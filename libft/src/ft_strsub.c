/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 11:18:52 by paperrin          #+#    #+#             */
/*   Updated: 2016/11/07 17:33:53 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	i;

	if (!s)
		return (NULL);
	ret = (char*)malloc(sizeof(char) * (len + 1));
	if (ret)
	{
		i = 0;
		while (i < len)
		{
			ret[i] = s[start + i];
			i++;
		}
		ret[i] = '\0';
	}
	return (ret);
}
