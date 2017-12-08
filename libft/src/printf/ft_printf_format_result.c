/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_format_result.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 11:20:34 by paperrin          #+#    #+#             */
/*   Updated: 2017/07/26 19:32:19 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		add_field(t_string *str, uint16_t flags
		, const t_printf_field *field)
{
	char	pad_char;
	char	*tmp;
	size_t	copy_pos;

	pad_char = ' ';
	if ((printf_flag_0 & flags) && (field->precision <= 0)
			&& !(printf_flag_minus & flags))
		pad_char = '0';
	if ((unsigned int)field->min > str->n)
	{
		if (!(tmp = ft_strnew(field->min)))
		{
			ft_strdel(&str->s);
			return (0);
		}
		ft_memset(tmp, pad_char, field->min);
		copy_pos = field->min - str->n;
		if (printf_flag_minus & flags)
			copy_pos = 0;
		ft_strncpy(tmp + copy_pos, str->s, str->n);
		ft_strdel(&str->s);
		str->s = tmp;
		str->n = field->min;
	}
	return (1);
}

static int		add_precision(t_string *str, char type
		, const t_printf_field *field)
{
	char	*tmp;

	if (field->precision < 0)
		return (1);
	if ('s' == type && (unsigned int)field->precision < str->n
			&& str->s[0] != '\0')
	{
		if (!(tmp = ft_strndup(str->s, field->precision)))
			return (0);
		ft_strdel(&str->s);
		str->s = tmp;
		str->n = field->precision;
	}
	else if (ft_strchr("dDiuU", type)
			&& (unsigned int)field->precision > str->n)
	{
		if (!(tmp = ft_strnew(field->precision)))
			return (0);
		ft_memset(tmp, '0', field->precision - str->n);
		ft_strcpy(tmp + field->precision - str->n, str->s);
		ft_strdel(&str->s);
		str->s = tmp;
		str->n = field->precision;
	}
	return (1);
}

static int		move_prefix(t_string *str, char type, uint16_t flags)
{
	char	*symbol_pos;
	char	*first_pos;
	char	*search;

	if (!(printf_flag_0 & flags) || printf_flag_minus & flags)
		return (1);
	if (ft_strchr("diu", type))
		search = "+- ";
	else if (ft_strchr("xX", type))
		search = "xX";
	else
		return (1);
	if (!(symbol_pos = ft_strchr_any(str->s, search)))
		return (1);
	if (!(first_pos = ft_strchr(str->s, '0')))
		return (0);
	first_pos[search[0] == 'x'] = *symbol_pos;
	if (symbol_pos != first_pos + (search[0] == 'x'))
		*symbol_pos = '0';
	return (1);
}

int				ft_printf_format_result(t_string *str, char type
		, uint16_t flags, const t_printf_field *field)
{
	if (!add_precision(str, type, field))
	{
		ft_strdel(&str->s);
		return (0);
	}
	if (!add_field(str, flags, field))
		return (0);
	if (field->precision == -1 && !move_prefix(str, type, flags))
		return (0);
	return (1);
}
