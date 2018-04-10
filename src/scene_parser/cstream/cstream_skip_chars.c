/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstream_skip_chars.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 18:22:10 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/09 16:34:37 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/cstream.h"

void		cstream_skip_chars(t_char_stream *const cstream,
		char const *const chars)
{
	char		c;

	while ((c = cstream_peek(cstream)) != '\0')
	{
		if (!ft_strchr(chars, c))
			return ;
		cstream_next(cstream);
	}
}

void		cstream_skip_to_chars(t_char_stream *const cstream,
		char const *const chars)
{
	char		c;

	while ((c = cstream_peek(cstream)) != '\0')
	{
		if (ft_strchr(chars, c))
			return ;
		cstream_next(cstream);
	}
}

void		cstream_skip_whitespaces(t_char_stream *const cstream)
{
	cstream_skip_chars(cstream, " \t\n\v\f\r");
}
