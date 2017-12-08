/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 11:19:56 by paperrin          #+#    #+#             */
/*   Updated: 2016/11/07 17:33:44 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	int		i_b;
	int		i_l;

	if (!*little)
		return ((char*)big);
	i_b = 0;
	while (big[i_b])
	{
		i_l = 0;
		while (little[i_l] && big[i_b + i_l] == little[i_l])
			i_l++;
		if (!little[i_l])
			return ((char*)&big[i_b]);
		i_b++;
	}
	return (NULL);
}
