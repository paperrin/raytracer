/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkstream_read_op.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 22:35:42 by paperrin          #+#    #+#             */
/*   Updated: 2018/03/04 23:29:33 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser.h"

t_token			*tkstream_read_op(t_token_stream *const tkstream)
{
	char		c;

	c = cstream_peek(tkstream->cstream);
	if (!ft_strchr(".-+", c))
	{
		free(tkstream->cur);
		ft_dprintf(STDERR_FILENO, "error: \"%c\" operator unsupported\n", c);
		return (NULL);
	}
	tkstream->cur->type = token_type_op;
	tkstream->cur->as.op.value = cstream_next(tkstream->cstream);
	return (tkstream->cur);
}

void			tkstream_print_op(t_token const *const token)
{
	ft_printf("{\n\ttype: op,\n\tvalue: \'%c\'\n}\n", token->as.punc.value);
}
