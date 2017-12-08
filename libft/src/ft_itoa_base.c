/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/11 12:28:54 by paperrin          #+#    #+#             */
/*   Updated: 2017/08/02 18:57:43 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	decimal_places(uintmax_t nb, unsigned int base)
{
	size_t	decimal_places;

	decimal_places = 1;
	while (nb > (base - 1))
	{
		nb /= base;
		decimal_places++;
	}
	return (decimal_places);
}

char			*ft_uitoa_base(uintmax_t nb, unsigned int base)
{
	int		len;
	char	c;
	char	*ret;

	len = decimal_places(nb, base);
	if (!(ret = ft_strnew(len)))
		return (NULL);
	while (len > 0)
	{
		c = '0' + nb % base;
		if (c > '9')
			c = 'a' + nb % base - 10;
		ret[--len] = c;
		nb /= base;
	}
	return (ret);
}

char			*ft_itoa_base(intmax_t nb, unsigned int base)
{
	char		*ret;
	char		*minus;
	uintmax_t	unb;

	unb = (nb < 0 ? (intmax_t)-nb : nb);
	if (!(ret = ft_uitoa_base(unb, base)))
		return (NULL);
	if (nb < 0 && base == 10)
	{
		minus = "-";
		return (ft_strjoin_free(&minus, &ret, STRJOIN_FREE_S2));
	}
	return (ret);
}
