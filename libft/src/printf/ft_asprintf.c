/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_asprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 13:40:25 by paperrin          #+#    #+#             */
/*   Updated: 2016/12/14 18:13:35 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				ft_asprintf(char **str, const char *format, ...)
{
	va_list		ap;
	int			ret;

	va_start(ap, format);
	ret = ft_vasprintf(str, format, ap);
	va_end(ap);
	return (ret);
}

int				ft_vasprintf(char **str, const char *format, va_list ap)
{
	return (ft_printf_core(str, format, ap));
}
