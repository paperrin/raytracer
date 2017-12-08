/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 19:15:21 by paperrin          #+#    #+#             */
/*   Updated: 2017/12/06 15:43:37 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <math.h>
#include <stdlib.h>

static char		*get_decimal_part(intmax_t d_part, unsigned int n_decimal)
{
	char		*zeros;
	char		*d_str;
	char		*str;
	size_t		i;

	n_decimal -= floor(log10(d_part));
	if (!(zeros = (char*)malloc(sizeof(*zeros) * n_decimal + 1)))
		return (NULL);
	i = 0;
	while (i < n_decimal - 1)
	{
		zeros[i] = '0';
		i++;
	}
	zeros[i] = '\0';
	if (!(d_str = ft_itoa(d_part)))
	{
		free(zeros);
		return (NULL);
	}
	str = ft_strjoin(zeros, d_str);
	free(zeros);
	free(d_str);
	return (str);
}

static char		*combine_nb(intmax_t i_part, intmax_t d_part,
		unsigned int n_decimal, const char *sep)
{
	char	*str;
	char	*i_str;
	char	*d_str;

	if (!(str = ft_itoa(i_part)))
		return (NULL);
	if (d_part > 0 && (i_str = ft_strjoin(str, sep)))
	{
		free(str);
		if (!(d_str = get_decimal_part(d_part, n_decimal)))
		{
			free(i_str);
			return (NULL);
		}
		if (!(str = ft_strjoin(i_str, d_str)))
		{
			free(i_str);
			free(d_str);
		}
	}
	return (str);
}

char			*ft_ftoa(long double nb, unsigned int n_decimal,
		const char *sep)
{
	char			*str;
	intmax_t		i_part;
	intmax_t		d_part;
	unsigned int	mult;

	i_part = (intmax_t)nb;
	d_part = -1;
	if (n_decimal > 0)
	{
		if (n_decimal > 9)
			n_decimal = 9;
		mult = pow(10, n_decimal);
		d_part = ABS((intmax_t)(nb * mult) % mult);
	}
	str = combine_nb(i_part, d_part, n_decimal, sep);
	return (str);
}
