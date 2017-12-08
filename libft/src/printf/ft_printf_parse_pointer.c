/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parse_pointer.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 17:16:02 by paperrin          #+#    #+#             */
/*   Updated: 2017/07/25 23:17:07 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_string		ft_printf_parse_pointer(const char *format, va_list ap
		, uint16_t flags, t_printf_field field)
{
	t_string	ret;

	(void)format;
	flags &= ~(printf_flag_l | printf_flag_ll | printf_flag_h | printf_flag_hh);
	flags |= printf_flag_alt | printf_flag_l | printf_flag_pointer;
	ret = ft_printf_parse_int("x", ap, flags, field);
	return (ret);
}
