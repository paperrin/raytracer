/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_dec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/24 16:54:01 by paperrin          #+#    #+#             */
/*   Updated: 2017/07/26 19:02:38 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static	char	*alloc_new_str(char **str, int prefix_len, int str_len)
{
	char	*new_str;

	new_str = ft_strnew(str_len + prefix_len + 1);
	if (!new_str)
	{
		free(*str);
		return (NULL);
	}
	ft_memset(new_str, '0', prefix_len);
	return (new_str);
}

char			*ft_itoa_dec(intmax_t nb, int alt, char prefix, int precision)
{
	char	*str;
	char	*new_str;
	int		str_len;
	int		prefix_len;

	if (nb == 0 && precision == 0 && !alt)
		return (ft_strnew(0));
	if (!(str = ft_uitoa(nb < 0 ? ~nb + 1 : nb)))
		return (NULL);
	str_len = ft_strlen(str);
	prefix = (nb < 0) ? '-' : prefix;
	if (precision > str_len || (!alt && nb != 0) || (nb == 0 && prefix))
	{
		prefix_len = prefix != '\0';
		if (precision > str_len)
			prefix_len += precision - str_len;
		if (!(new_str = alloc_new_str(&str, prefix_len, str_len)))
			return (NULL);
		if (prefix != '\0')
			new_str[0] = prefix;
		ft_strcpy(new_str + prefix_len, str);
		free(str);
		str = new_str;
	}
	return (str);
}

char			*ft_uitoa_dec(uintmax_t nb, int alt, char prefix, int precision)
{
	char	*str;
	char	*new_str;
	int		str_len;
	int		prefix_len;

	if (nb == 0 && precision == 0 && !alt)
		return (ft_strnew(0));
	if (!(str = ft_uitoa(nb)))
		return (NULL);
	str_len = ft_strlen(str);
	if (precision > str_len || (!alt && nb != 0))
	{
		prefix_len = prefix != '\0';
		if (precision > str_len)
			prefix_len += precision - str_len;
		if (!(new_str = alloc_new_str(&str, prefix_len, str_len)))
			return (NULL);
		ft_strcpy(new_str + prefix_len, str);
		free(str);
		str = new_str;
	}
	return (str);
}
