/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkstream_read_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 18:50:03 by paperrin          #+#    #+#             */
/*   Updated: 2018/03/24 00:00:45 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser.h"

static char		*concat_char_is_escaped(char **str, char c, int escaped)
{
	if (c == '"')
		escaped = 0;
	if (!escaped)
	{
		if (!(*str = ft_strjoin_char_free(str, c, 1, STRJOIN_FREE_S1)))
			return (perror_string(ERR_MEMORY));
	}
	else if (c != '"')
	{
		if (!(*str = ft_strjoin_char_free(str, '\\', 1, STRJOIN_FREE_S1)))
			return (perror_string(ERR_MEMORY));
		if (!(*str = ft_strjoin_char_free(str, c, 1, STRJOIN_FREE_S1)))
			return (perror_string(ERR_MEMORY));
	}
	return (*str);
}

t_token			*tkstream_read_str(t_token_stream *const tkstream)
{
	char		*str;
	char		c;
	int			escaped;

	cstream_next(tkstream->cstream);
	str = NULL;
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
			return (NULL);
		}
	}
	tkstream->cur->type = token_type_str;
	tkstream->cur->as.str.value = str;
	return (tkstream->cur);
}

void			tkstream_print_str(t_token const *const token)
{
	ft_printf("{\n\ttype: str,\n\tvalue: \"%s\"\n}\n", token->as.str.value);
}
