/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/29 14:19:48 by paperrin          #+#    #+#             */
/*   Updated: 2017/07/29 15:30:59 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				ft_sprintf(char *str, const char *format, ...)
{
	va_list		ap;
	int			ret;

	va_start(ap, format);
	ret = ft_vsprintf(str, format, ap);
	va_end(ap);
	return (ret);
}

int				ft_vsprintf(char *str, const char *format, va_list ap)
{
	char		*allocated_str;
	int			len;

	len = ft_printf_core(&allocated_str, format, ap);
	if (allocated_str)
	{
		ft_memcpy(str, allocated_str, len + 1);
		ft_strdel(&allocated_str);
	}
	return (len);
}
