/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/04 15:37:25 by paperrin          #+#    #+#             */
/*   Updated: 2017/12/05 15:16:48 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void					init_flag_list(void **flag_list)
{
	static int		is_set = 0;

	if (is_set)
		return ;
	is_set = 1;
	ft_tab_init(flag_list, (FT_PRINTF_NB_FLAGS) * 2
		, "#"	, (void*)printf_flag_alt
		, "0"	, (void*)printf_flag_0
		, "-"	, (void*)printf_flag_minus
		, "+"	, (void*)printf_flag_plus
		, " "	, (void*)printf_flag_space
		, "hh"	, (void*)printf_flag_hh
		, "h"	, (void*)printf_flag_h
		, "ll"	, (void*)printf_flag_ll
		, "l"	, (void*)printf_flag_l
		, "j"	, (void*)printf_flag_j
		, "z"	, (void*)printf_flag_z);
}

static void					get_parser_list(void **parser_list)
{
	static int		is_set = 0;

	if (is_set)
		return ;
	is_set = 1;
	ft_tab_init(parser_list, (FT_PRINTF_NB_PARSERS) * 2
		, "dDioOuUxXb"	, &ft_printf_parse_int
		, "cC"			, &ft_printf_parse_char
		, "p"			, &ft_printf_parse_pointer
		, "sS"			, &ft_printf_parse_string
		, "%"			, &ft_printf_parse_none);
}

static int					set_flag(uint16_t *flags, const char *format)
{
	static void		*flag_list[FT_PRINTF_NB_FLAGS * 2];
	int				flag_len;
	int				i;

	init_flag_list(flag_list);
	i = 0;
	while (i < FT_PRINTF_NB_FLAGS * 2)
	{
		flag_len = ft_strlen(flag_list[i]);
		if (ft_strnstr(format, flag_list[i], flag_len))
		{
			*flags |= (int)flag_list[i + 1];
			return (flag_len);
		}
		i += 2;
	}
	return (0);
}

static t_printf_parser		get_parser(char *format)
{
	static void		*parser_list[FT_PRINTF_NB_PARSERS * 2];
	int				i;

	get_parser_list(parser_list);
	i = 0;
	while (i < FT_PRINTF_NB_PARSERS * 2)
	{
		if (ft_strchr(parser_list[i], *format))
			return ((t_printf_parser)parser_list[i + 1]);
		i += 2;
	}
	return (NULL);
}

t_string					ft_printf_parse(char *format, va_list ap,
		int *format_len)
{
	t_printf_parser			f_parse;
	t_printf_field			field;
	int						flag_len;
	uint16_t				flags;
	t_string				ret;

	ret = ft_string(NULL, 0);
	f_parse = NULL;
	field = ft_printf_field(0, -1);
	flags = 0;
	*format_len = 1;
	flag_len = 0;
	while (format[*format_len] && !f_parse && ((*format_len) += flag_len))
		if (!(flag_len = set_flag(&flags, &format[*format_len]))
		&& (!(f_parse = get_parser(&format[*format_len])))
		&& !(flag_len = ft_printf_parse_field(&field, &format[*format_len])))
		{
			*format_len -= 1;
			return (ft_string(ft_strnew(0), 0));
		}
	if (!f_parse)
		return (ret);
	ret = (*f_parse)(format + *format_len, ap, flags, field);
	return (ret);
}
