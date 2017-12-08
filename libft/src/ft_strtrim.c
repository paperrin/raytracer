/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 11:51:36 by paperrin          #+#    #+#             */
/*   Updated: 2016/11/07 17:37:21 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t	len;
	char	*ret;

	if (!s)
		return (NULL);
	len = 0;
	while (*s == ' ' || *s == '\n' || *s == '\t')
		s++;
	len = ft_strlen(s);
	if (len > 0)
		len--;
	while (s[len] == ' ' || s[len] == '\n' || s[len] == '\t')
		len--;
	ret = ft_strsub(s, 0, len + 1);
	return (ret);
}
