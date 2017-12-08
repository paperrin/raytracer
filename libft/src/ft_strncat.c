/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 17:42:03 by paperrin          #+#    #+#             */
/*   Updated: 2016/11/07 17:29:10 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	char	*dst;

	dst = s1;
	while (*dst)
		dst++;
	while (n--)
	{
		if (!(*dst = *s2++))
			break ;
		dst++;
	}
	*dst = '\0';
	return (s1);
}
