/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkstream_read_punc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 20:54:10 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/09 16:59:53 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/tkstream.h"

t_token			*tkstream_read_punc(t_token_stream *const tkstream)
{
	char		c;

	c = cstream_peek(tkstream->cstream);
	if (!ft_strchr(",()", c))
	{
		ft_memdel((void**)&tkstream->cur);
		return (tkstream_pferror(tkstream, "unsupported punctuation"));
	}
	tkstream->cur->type = token_type_punc;
	tkstream->cur->as.punc.value = cstream_next(tkstream->cstream);
	return (tkstream->cur);
}
