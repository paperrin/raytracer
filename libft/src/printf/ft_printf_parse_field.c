/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parse_field.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 17:19:18 by paperrin          #+#    #+#             */
/*   Updated: 2016/12/12 17:14:10 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printf_parse_field(t_printf_field *field, const char *format)
{
	int		len;
	int		i;

	len = 0;
	while (ft_isdigit(format[len]))
		len++;
	if (len > 0)
		field->min = ft_atoi(format);
	if (format[len] == '.')
	{
		len++;
		i = 0;
		while (ft_isdigit(format[len + i]))
			i++;
		if (i > 0)
			field->precision = ft_atoi(&format[len]);
		else
			field->precision = 0;
		len += i;
	}
	return (len);
}
