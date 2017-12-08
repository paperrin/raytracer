/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_get_bracket_str.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/26 21:34:47 by paperrin          #+#    #+#             */
/*   Updated: 2017/07/26 23:02:33 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		init_bracket_list(void **bracket_list)
{
	static int		is_set = 0;

	if (is_set)
		return ;
	is_set = 1;
	ft_tab_init(bracket_list, (FT_PRINTF_NB_BRACKETS) * 2
		, "{eoc}"		, "\x1b[0m"			, "{bold}"		, "\x1b[1;1m"
		, "{underline}"	, "\x1b[4;1m"		, "{blink}"		, "\x1b[5;1m"
		, "{highlight}"	, "\x1b[7;1m"
		, "{black}"		, "\x1b[30;1m"		, "{red}"		, "\x1b[31;1m"
		, "{green}"		, "\x1b[32;1m"		, "{yellow}"	, "\x1b[33;1m"
		, "{blue}"		, "\x1b[34;1m"		, "{pink}"		, "\x1b[35;1m"
		, "{cyan}"		, "\x1b[36;1m"		, "{gray}"		, "\x1b[37;1m"
		, "{bblack}"	, "\x1b[40;1m"		, "{bred}"		, "\x1b[41;1m"
		, "{bgreen}"	, "\x1b[42;1m"		, "{byellow}"	, "\x1b[43;1m"
		, "{bblue}"		, "\x1b[44;1m"		, "{bpink}"		, "\x1b[45;1m"
		, "{bcyan}"		, "\x1b[46;1m"		, "{bgray}"		, "\x1b[47;1m");
}

int				ft_printf_get_bracket_str(const char *format
		, char **bracket_str)
{
	static void		*bracket_list[FT_PRINTF_NB_BRACKETS * 2];
	int				bracket_len;
	int				i;

	init_bracket_list(bracket_list);
	i = 0;
	while (i < FT_PRINTF_NB_BRACKETS * 2)
	{
		bracket_len = ft_strlen(bracket_list[i]);
		if (ft_strnstr(format, bracket_list[i], bracket_len))
		{
			*bracket_str = ft_strdup((char*)bracket_list[i + 1]);
			if (!(*bracket_str))
				return (-1);
			return (bracket_len);
		}
		i += 2;
	}
	return (0);
}
