/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parse_char.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 16:38:53 by paperrin          #+#    #+#             */
/*   Updated: 2017/12/05 15:20:18 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_string		parse(char type, va_list ap, uint16_t flags)
{
	t_string	ret;
	wchar_t		wc;
	int			i;
	char		c;

	ret = ft_string(NULL, 0);
	if ('C' == type || (printf_flag_l & flags))
	{
		wc = va_arg(ap, wint_t);
		if (!(ret.s = ft_strnew(ft_wchar_len(wc))))
			return (ret);
		i = 0;
		while ((c = ft_wchar_char_at(wc, i)) != -1)
			ret.s[i++] = c;
		ret.n = i;
	}
	else
	{
		if (!(ret.s = ft_strnew(1)))
			return (ret);
		ret.s[0] = (char)va_arg(ap, int);
		ret.n = 1;
	}
	return (ret);
}

t_string			ft_printf_parse_char(const char *format, va_list ap
		, uint16_t flags, t_printf_field field)
{
	t_string	ret;

	ret = ft_string(NULL, 0);
	ret = parse(*format, ap, flags);
	if (!ret.s)
		return (ret);
	if (!ft_printf_format_result(&ret, *format, flags, &field))
		return (ret);
	return (ret);
}
