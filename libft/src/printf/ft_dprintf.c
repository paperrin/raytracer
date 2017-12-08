/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/29 15:38:44 by paperrin          #+#    #+#             */
/*   Updated: 2017/07/29 16:52:25 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				ft_dprintf(int fd, const char *format, ...)
{
	va_list		ap;
	int			ret;

	va_start(ap, format);
	ret = ft_vdprintf(fd, format, ap);
	va_end(ap);
	return (ret);
}

int				ft_vdprintf(int fd, const char *format, va_list ap)
{
	int			ret;
	char		*str;

	if (fd < 0)
		return (-1);
	ret = ft_printf_core(&str, format, ap);
	if (str)
	{
		ret = write(fd, str, ret);
		ft_strdel(&str);
	}
	return (ret);
}
