/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 16:18:38 by paperrin          #+#    #+#             */
/*   Updated: 2016/11/25 16:52:23 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_hash.h"

t_hash	ft_hash_string(char *s)
{
	t_hash				hash;
	t_hash				remn;
	static const size_t	shift = sizeof(*s) * 8 / 2;
	static const size_t size = sizeof(hash) * 8;
	int					i;

	hash = 0;
	remn = 0;
	i = -1;
	while (s[++i])
	{
		hash += s[i];
		if (!s[i + 1])
			break ;
		hash += remn;
		remn = hash >> (size - shift);
		hash = hash << shift;
	}
	return (hash);
}
