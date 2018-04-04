/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkstream_read_punc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 20:54:10 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/04 17:47:30 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser.h"

t_token			*tkstream_read_punc(t_token_stream *const tkstream)
{
	char		c;

	c = cstream_peek(tkstream->cstream);
	if (!ft_strchr(",()", c))
	{
		ft_memdel((void**)&tkstream->cur);
		ft_dprintf(STDERR_FILENO, "error: \"%c\" punctuation unsupported\n", c);
		return (NULL);
	}
	tkstream->cur->type = token_type_punc;
	tkstream->cur->as.punc.value = cstream_next(tkstream->cstream);
	return (tkstream->cur);
}
