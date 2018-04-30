/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkstream_read_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 18:50:03 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/11 19:59:06 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/tkstream.h"

static char		*concat_char_is_escaped(char **str, char c, int escaped)
{
	if (c == '"')
		escaped = 0;
	if (!escaped)
	{
		if (!(*str = ft_strjoin_char_free(str, c, 1, STRJOIN_FREE_S1)))
			return (NULL);
	}
	else if (c != '"')
	{
		if (!(*str = ft_strjoin_char_free(str, '\\', 1, STRJOIN_FREE_S1)))
			return (NULL);
		if (!(*str = ft_strjoin_char_free(str, c, 1, STRJOIN_FREE_S1)))
			return (NULL);
	}
	return (*str);
}

static void		replace_esc_codes(char **str)
{
	static char		*esc_codes[TKSTREAM_NB_ESC_CODES * 2] = {
		"\\n", "\n",
		"\\t", "\t",
		"\\r", "\r",
		"\\v", "\v",
		"\\f", "\f"};
	int				i;
	char			*s;

	i = -1;
	while (++i < TKSTREAM_NB_ESC_CODES)
	{
		s = *str;
		while ((s = ft_strstr(s, esc_codes[i * 2])))
		{
			*s = *esc_codes[i * 2 + 1];
			ft_strcpy(&s[1], &s[2]);
		}
	}
}

t_token			*tkstream_read_str(t_token_stream *const tkstream)
{
	char		*str;
	char		c;
	int			escaped;

	cstream_next(tkstream->cstream);
	if (!(str = ft_strnew(0)))
		return (tkstream_perror(tkstream, ERR_MEMORY));
	while ((c = cstream_next(tkstream->cstream)))
	{
		escaped = (c == '\\');
		if (escaped)
			c = cstream_next(tkstream->cstream);
		if (c == '"' && !escaped)
			break ;
		if (!concat_char_is_escaped(&str, c, escaped))
		{
			ft_strdel(&str);
			return (tkstream_perror(tkstream, ERR_MEMORY));
		}
	}
	replace_esc_codes(&str);
	tkstream->cur->type = token_type_str;
	tkstream->cur->as.str.value = str;
	return (tkstream->cur);
}
