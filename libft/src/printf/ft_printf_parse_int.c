/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parse_int.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/04 18:49:58 by paperrin          #+#    #+#             */
/*   Updated: 2017/07/25 20:54:04 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_string		parse(char type, va_list ap, uint16_t flags
		, int precision)
{
	if (ft_strchr("DOU", type))
	{
		type = ft_tolower(type);
		flags &= ~printf_flag_ll;
		flags |= printf_flag_l;
	}
	return (ft_printf_parse_number(type, ap, flags, precision));
}

t_string			ft_printf_parse_int(const char *format, va_list ap
		, uint16_t flags, t_printf_field field)
{
	t_string	ret;

	ret = parse(*format, ap, flags, field.precision);
	if (!ret.s)
		return (ret);
	if (!ft_printf_format_result(&ret, *format, flags, &field))
		return (ret);
	return (ret);
}
