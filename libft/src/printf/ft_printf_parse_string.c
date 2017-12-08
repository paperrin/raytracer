/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parse_string.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 17:14:49 by paperrin          #+#    #+#             */
/*   Updated: 2017/12/05 15:21:14 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void			parse_ws(t_string *ret, va_list ap, t_printf_field *field)
{
	wchar_t		*ws;
	size_t		n_char;
	size_t		str_len;

	if (!(ws = va_arg(ap, wchar_t*)))
		*ret = ft_string(ft_strdup("(null)"), 6);
	else
	{
		str_len = ft_wstrlen_char(ws);
		if (field->precision > -1 && (unsigned)field->precision < str_len)
			n_char = field->precision;
		else
			n_char = str_len;
		ret->n = ft_wstrnlen_char(ws, n_char);
		ret->s = ft_strdupw_nchar(ws, n_char);
	}
}

static void			parse_s(t_string *ret, va_list ap, t_printf_field *field)
{
	char		*s;
	size_t		n_char;
	size_t		str_len;

	if (!(s = va_arg(ap, char*)))
		*ret = ft_string(ft_strdup("(null)"), 6);
	else
	{
		str_len = ft_strlen(s);
		if (field->precision > -1 && (unsigned)field->precision < str_len)
			n_char = field->precision;
		else
			n_char = str_len;
		ret->n = n_char;
		ret->s = ft_strndup(s, n_char);
	}
}

static t_string		parse(char type, va_list ap, uint16_t flags
		, t_printf_field *field)
{
	t_string	ret;

	ret = ft_string(NULL, 0);
	if ('S' == type || (printf_flag_l & flags))
		parse_ws(&ret, ap, field);
	else
		parse_s(&ret, ap, field);
	return (ret);
}

t_string			ft_printf_parse_string(const char *format, va_list ap
		, uint16_t flags, t_printf_field field)
{
	t_string	ret;

	ret = ft_string(NULL, 0);
	ret = parse(*format, ap, flags, &field);
	if (!ret.s)
		return (ret);
	if (!ft_printf_format_result(&ret, *format, flags, &field))
		return (ret);
	return (ret);
}
