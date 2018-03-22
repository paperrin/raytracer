/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 16:29:36 by paperrin          #+#    #+#             */
/*   Updated: 2018/03/14 21:58:48 by ilarbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>
# include <string.h>
# include <stdint.h>
# include <stdlib.h>
# include "my_unistd.h"

# define FT_PRINTF_NB_FLAGS 11
# define FT_PRINTF_NB_BRACKETS 21
# define FT_PRINTF_NB_PARSERS 5

typedef struct	s_printf_field
{
	int			min;
	int			precision;
}				t_printf_field;

typedef t_string	(*t_printf_parser)(char*, va_list
		, uint16_t, t_printf_field);

typedef enum	e_printf_flags
{
	printf_flag_alt = 1 << 0,
	printf_flag_0 = 1 << 1,
	printf_flag_minus = 1 << 2,
	printf_flag_plus = 1 << 3,
	printf_flag_space = 1 << 4,
	printf_flag_h = 1 << 5,
	printf_flag_hh = 1 << 6,
	printf_flag_l = 1 << 7,
	printf_flag_ll = 1 << 8,
	printf_flag_j = 1 << 9,
	printf_flag_z = 1 << 10,
	printf_flag_pointer = 1 << 11
}				t_printf_flags;

int				ft_asprintf(char **ret, const char *format, ...);
int				ft_vasprintf(char **ret, const char *format, va_list ap);

int				ft_snprintf(char *str, size_t size, const char *format, ...);
int				ft_vsnprintf(char *str, size_t size, const char *format
		, va_list ap);

int				ft_sprintf(char *str, const char *format, ...);
int				ft_vsprintf(char *str, const char *format, va_list ap);

int				ft_dprintf(int fd, const char *format, ...);
int				ft_vdprintf(int fd, const char *format, va_list ap);

int				ft_printf(const char *format, ...);
int				ft_vprintf(const char *format, va_list ap);

t_printf_field	ft_printf_field(int min, int precision);

int				ft_printf_core(char **str, const char *format, va_list ap);
t_string		ft_printf_parse(char *format, va_list ap, int *esc_seq_len);
int				ft_printf_parse_field(t_printf_field *field
		, const char *format);
t_string		ft_printf_parse_number(char type, va_list ap, uint16_t flags
		, int precision);
t_string		ft_printf_parse_int(const char *format, va_list ap
		, uint16_t flags, t_printf_field field);
t_string		ft_printf_parse_char(const char *format, va_list ap
		, uint16_t flags, t_printf_field field);
t_string		ft_printf_parse_string(const char *format, va_list ap
		, uint16_t flags, t_printf_field field);
t_string		ft_printf_parse_pointer(const char *format, va_list ap
		, uint16_t flags, t_printf_field field);
t_string		ft_printf_parse_none(const char *format, va_list ap
		, uint16_t flags, t_printf_field field);
int				ft_printf_format_result(t_string *str, char type
		, uint16_t flags, const t_printf_field *field);
int				ft_printf_get_bracket_str(const char *format
		, char **bracket_str);

#endif
