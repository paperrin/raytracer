/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parse_number.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/24 16:20:37 by paperrin          #+#    #+#             */
/*   Updated: 2017/12/05 15:19:44 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static intmax_t		get_signed(va_list ap, uint16_t flags)
{
	if (flags & printf_flag_ll)
		return (va_arg(ap, long long));
	else if (flags & printf_flag_l)
		return (va_arg(ap, long));
	else if (flags & printf_flag_j)
		return (va_arg(ap, intmax_t));
	else if (flags & printf_flag_z)
		return (va_arg(ap, size_t));
	else if (flags & printf_flag_hh)
		return ((char)va_arg(ap, size_t));
	else if (flags & printf_flag_h)
		return ((short)va_arg(ap, size_t));
	return (va_arg(ap, int));
}

static uintmax_t	get_unsigned(va_list ap, uint16_t flags)
{
	if (flags & printf_flag_ll)
		return (va_arg(ap, unsigned long long));
	else if (flags & printf_flag_l)
		return (va_arg(ap, unsigned long));
	else if (flags & printf_flag_j)
		return (va_arg(ap, uintmax_t));
	else if (flags & printf_flag_z)
		return (va_arg(ap, size_t));
	else if (flags & printf_flag_hh)
		return ((unsigned char)va_arg(ap, size_t));
	else if (flags & printf_flag_h)
		return ((unsigned short)va_arg(ap, size_t));
	return (va_arg(ap, unsigned int));
}

static t_string		parse_special(char type, uintmax_t nb, uint16_t flags
		, int precision)
{
	int			prefix;
	t_string	ret;

	prefix = (printf_flag_alt & flags);
	if (printf_flag_pointer & flags)
		prefix = 2;
	ret = ft_string(NULL, 0);
	if ('o' == type)
		ret.s = ft_itoa_oct(nb, prefix, precision);
	else if ('b' == type)
		ret.s = ft_itoa_bin(nb, prefix, precision);
	else
	{
		ret.s = ft_itoa_hex(nb, prefix, precision);
		if (ret.s && type == 'X')
			ret.s = ft_strupr(ret.s);
	}
	return (ret);
}

t_string			ft_printf_parse_number(char type, va_list ap, uint16_t flags
		, int precision)
{
	t_string	ret;
	char		prefix;

	prefix = '\0';
	if (printf_flag_plus & flags)
		prefix = '+';
	else if (printf_flag_space & flags)
		prefix = ' ';
	ret = ft_string(NULL, 0);
	if (ft_strchr("di", type))
		ret.s = ft_itoa_dec(get_signed(ap, flags), printf_flag_alt & flags,
				prefix, precision);
	else
	{
		if ('u' == type)
			ret.s = ft_uitoa_dec(get_unsigned(ap, flags)
					, printf_flag_alt & flags, '\0', precision);
		else if (ft_strchr("xXob", type))
			ret = parse_special(type, get_unsigned(ap, flags)
					, flags, precision);
	}
	if (ret.s)
		ret.n = ft_strlen(ret.s);
	return (ret);
}
