/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkstream_read_num.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 21:21:52 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/09 16:59:53 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/tkstream.h"

t_token			*tkstream_read_num(t_token_stream *const tkstream)
{
	char		*str;
	char		c;

	str = NULL;
	while ((c = cstream_peek(tkstream->cstream)))
	{
		if (!ft_strchr("0123456789.", c))
			break ;
		if (!(str = ft_strjoin_char_free(&str, c, 1, STRJOIN_FREE_S1)))
			return (tkstream_perror(tkstream, ERR_MEMORY));
		cstream_next(tkstream->cstream);
	}
	tkstream->cur->type = token_type_num;
	tkstream->cur->as.num.value = ft_atof(str, '.');
	ft_strdel(&str);
	return (tkstream->cur);
}
