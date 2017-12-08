/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_snprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/29 14:53:33 by paperrin          #+#    #+#             */
/*   Updated: 2017/07/29 16:57:17 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_snprintf(char *str, size_t n, const char *format, ...)
{
	va_list		ap;
	int			ret;

	va_start(ap, format);
	ret = ft_vsnprintf(str, n, format, ap);
	va_end(ap);
	return (ret);
}

int		ft_vsnprintf(char *str, size_t n, const char *format, va_list ap)
{
	char		*allocated_str;
	int			len;
	int			n_to_copy;

	len = ft_printf_core(&allocated_str, format, ap);
	if (allocated_str)
	{
		n_to_copy = ((long)n - 1 < (long)len ? n - (long)1 : len);
		if (n > 0)
		{
			ft_memcpy(str, allocated_str, len + 1);
			str[n_to_copy] = '\0';
		}
		ft_strdel(&allocated_str);
	}
	return (len);
}
