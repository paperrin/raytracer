/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkstream_read_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 18:50:03 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/09 16:59:53 by paperrin         ###   ########.fr       */
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
	tkstream->cur->type = token_type_str;
	tkstream->cur->as.str.value = str;
	return (tkstream->cur);
}
