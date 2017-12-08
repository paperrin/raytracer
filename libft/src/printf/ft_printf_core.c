/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_core.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 15:32:33 by paperrin          #+#    #+#             */
/*   Updated: 2017/12/05 15:11:53 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		add_value(t_string *str, const char *format, va_list ap
		, int *is_bracket)
{
	t_string	value;
	char		*concat;
	int			len;

	if (*format != '%')
		return (0);
	*is_bracket = 1;
	if (*format == '%' && !format[1])
	{
		if (!(str->s = ft_strnew(0)))
			return (-1);
		str->n = 0;
		return (1);
	}
	value = ft_printf_parse((char*)format, ap, &len);
	if (!value.s)
	{
		ft_strdel(&str->s);
		return (-1);
	}
	if (!(concat = ft_strnjoin_free(ft_strnjoin_arg(&str->s, str->n)
					, ft_strnjoin_arg(&value.s, value.n), STRJOIN_FREE_BOTH)))
		return (-1);
	*str = ft_string(concat, str->n + value.n);
	return (len + 1);
}

static int		add_text(t_string *str, const char *format, int is_bracket)
{
	char	*concat;
	int		i;

	i = 0;
	while (format[i] && format[i] != '%')
	{
		if (is_bracket && format[i] == '{')
			break ;
		i++;
	}
	if (i == 0)
		return (0);
	if (!(concat = ft_strnjoin_free(ft_strnjoin_arg(&str->s, str->n)
			, ft_strnjoin_arg((char**)&format, i), STRJOIN_FREE_S1)))
		return (-1);
	str->s = concat;
	str->n += i;
	return (i);
}

static int		add_color(t_string *str, const char *format, int *is_bracket)
{
	char	*concat;
	char	*bracket_str;
	int		len;
	int		bracket_str_len;

	*is_bracket = 0;
	if (*format != '{')
		return (0);
	len = ft_printf_get_bracket_str(format, &bracket_str);
	if (len <= 0)
		return (len);
	bracket_str_len = ft_strlen(bracket_str);
	if (!(concat = ft_strnjoin_free(ft_strnjoin_arg(&str->s, str->n)
			, ft_strnjoin_arg(&bracket_str, bracket_str_len)
			, STRJOIN_FREE_BOTH)))
		return (-1);
	str->s = concat;
	str->n += bracket_str_len;
	*is_bracket = 1;
	return (len);
}

int				ft_printf_core(char **str, const char *format, va_list ap)
{
	int			len;
	int			i;
	t_string	ret;
	int			is_bracket;

	ret.n = 0;
	if (!(ret.s = ft_strnew(0)))
		return (-1);
	i = 0;
	len = 0;
	is_bracket = 1;
	while (format[i])
	{
		if ((len = add_text(&ret, format + i, is_bracket)) < 0)
			return (-1);
		i += len;
		if ((len = add_color(&ret, format + i, &is_bracket)) < 0)
			return (-1);
		i += len;
		if ((len = add_value(&ret, format + i, ap, &is_bracket)) < 0)
			return (-1);
		i += len;
	}
	*str = ret.s;
	return (ret.n);
}
