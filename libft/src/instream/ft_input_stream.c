/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input_stream.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 18:08:18 by paperrin          #+#    #+#             */
/*   Updated: 2017/12/07 18:08:20 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_input_stream.h"
#include "internal_ft_input_stream.h"

int				ft_in_stream_next(t_in_stream *in_stream)
{
	return ((*in_stream->f_next)(in_stream));
}

int				ft_in_stream_nnext(t_in_stream *in_stream,
		char *buf, size_t n)
{
	int		byte;
	size_t	i;

	i = 0;
	byte = 0;
	while (i < n && (byte = (*in_stream->f_next)(in_stream)) >= 0)
	{
		buf[i] = byte;
		i++;
	}
	if (byte < 1)
		return (byte);
	return (i);
}

int				ft_in_stream_peek(t_in_stream *in_stream)
{
	return (in_stream->current);
}

size_t			ft_in_stream_available(t_in_stream *in_stream)
{
	return (in_stream->available);
}
