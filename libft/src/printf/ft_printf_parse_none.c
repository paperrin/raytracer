/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parse_none.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 17:16:30 by paperrin          #+#    #+#             */
/*   Updated: 2016/12/14 17:14:29 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_string		parse(char type, va_list ap, uint16_t flags)
{
	t_string	ret;

	(void)type;
	(void)ap;
	(void)flags;
	ret.s = ft_strdup("%");
	ret.n = 1;
	return (ret);
}

t_string			ft_printf_parse_none(const char *format, va_list ap
		, uint16_t flags, t_printf_field field)
{
	t_string	ret;

	(void)field;
	ret = parse(*format, ap, flags);
	if (!ret.s)
		return (ret);
	if (!ft_printf_format_result(&ret, *format, flags, &field))
		return (ret);
	return (ret);
}
