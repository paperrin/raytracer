/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/26 20:29:08 by paperrin          #+#    #+#             */
/*   Updated: 2017/07/26 20:32:40 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char		*add_prefix(char *str, uintmax_t nb, int prefix, int precision)
{
	int		prefix_len;
	char	*new_str;
	int		str_len;

	str_len = ft_strlen(str);
	if (precision > str_len || (prefix && nb != 0))
	{
		prefix_len = (prefix ? 2 : 0);
		if (precision > str_len)
			prefix_len += precision - str_len;
		new_str = ft_strnew(str_len + prefix_len + 1);
		if (!new_str)
		{
			free(str);
			return (NULL);
		}
		ft_memset(new_str, '0', prefix_len);
		if (prefix)
			new_str[1] = 'b';
		ft_strcpy(new_str + prefix_len, str);
		free(str);
		str = new_str;
	}
	return (str);
}

char			*ft_itoa_bin(uintmax_t nb, int prefix, int precision)
{
	char	*str;

	str = NULL;
	if (nb == 0 && precision == 0)
	{
		if (!(str = ft_strnew(0)))
			return (NULL);
	}
	if (!str && !(str = ft_uitoa_base(nb, 2)))
		return (NULL);
	str = add_prefix(str, nb, prefix, precision);
	return (str);
}
