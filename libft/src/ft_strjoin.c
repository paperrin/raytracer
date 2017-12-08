/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 11:33:17 by paperrin          #+#    #+#             */
/*   Updated: 2017/08/03 22:55:34 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	ret = (char*)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (ret)
	{
		ret = ft_strcpy(ret, s1);
		ft_strcpy(ret + s1_len, s2);
		ret[s1_len + s2_len] = '\0';
	}
	return (ret);
}

char	*ft_strjoin_free(char **a, char **b, int free)
{
	char	*ret;

	ret = ft_strjoin(*a, *b);
	if (!ret)
		return (NULL);
	if (free == STRJOIN_FREE_BOTH || free == STRJOIN_FREE_S1)
		ft_strdel(a);
	if (free == STRJOIN_FREE_BOTH || free == STRJOIN_FREE_S2)
		ft_strdel(b);
	return (ret);
}
