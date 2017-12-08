/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 11:32:49 by paperrin          #+#    #+#             */
/*   Updated: 2017/07/25 20:59:47 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	int		i_b;
	int		i_l;

	if (!*little)
		return ((char*)big);
	i_b = 0;
	while (big[i_b] && len)
	{
		i_l = 0;
		while (little[i_l] && big[i_b + i_l] == little[i_l])
			i_l++;
		if (!little[i_l] && len >= ft_strlen(little))
			return ((char*)&big[i_b]);
		i_b++;
		len--;
	}
	return (NULL);
}
