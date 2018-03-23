/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkstream.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 16:54:17 by paperrin          #+#    #+#             */
/*   Updated: 2018/03/23 21:54:20 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser.h"

t_token_stream		*tkstream_open(char const *const file_path)
{
	t_token_stream		*tkstream;

	if (!(tkstream = (t_token_stream*)malloc(sizeof(*tkstream))))
		return (perror_string(ERR_MEMORY));
	if (!(tkstream->cstream = cstream_open(file_path)))
	{
		ft_memdel((void**)&tkstream);
		return (NULL);
	}
	tkstream->cur = NULL;
	tkstream->col = 1;
	tkstream->line = 1;
	return (tkstream);
}

void				tkstream_close(t_token_stream **tkstream)
{
	cstream_close(&(*tkstream)->cstream);
	ft_memdel((void**)tkstream);
}

t_token				*tkstream_next(t_token_stream *const tkstream)
{
	cstream_skip_whitespaces(tkstream->cstream);
	if (cstream_peek(tkstream->cstream) == '\0')
		return (NULL);
	if (!tkstream_read_token(tkstream))
		return (NULL);
	return (tkstream->cur);
}

t_token				*tkstream_peek(t_token_stream *const tkstream)
{
	if (tkstream->cur)
		return (tkstream->cur);
	return (tkstream_next(tkstream));
}

int					tkstream_error(t_token_stream const *const tkstream,
		char const *const error)
{
	ft_dprintf(STDERR_FILENO, "%s:%u:%u: error: %s\n",
			tkstream->cstream->file_path,
			tkstream->line, tkstream->col, error);
	return (0);
}
