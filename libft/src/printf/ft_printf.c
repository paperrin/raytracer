/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 13:56:48 by paperrin          #+#    #+#             */
/*   Updated: 2017/12/05 15:14:06 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				ft_printf(const char *format, ...)
{
	va_list		ap;
	int			ret;

	va_start(ap, format);
	ret = ft_vprintf(format, ap);
	va_end(ap);
	return (ret);
}

int				ft_vprintf(const char *format, va_list ap)
{
	int			ret;
	char		*str;

	ret = ft_printf_core(&str, format, ap);
	if (str)
	{
		ft_putnstr(str, ret);
		ft_strdel(&str);
	}
	return (ret);
}
