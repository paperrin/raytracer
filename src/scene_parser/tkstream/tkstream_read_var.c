/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkstream_read_var.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 23:05:37 by paperrin          #+#    #+#             */
/*   Updated: 2018/03/15 17:28:14 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser.h"

t_token			*tkstream_read_var(t_token_stream *const tkstream)
{
	char		*str;
	char		c;

	str = NULL;
	while ((c = cstream_peek(tkstream->cstream)))
	{
		if (!(ft_isalnum(c) || ft_strchr("_", c)))
			break ;
		if (!(str = ft_strjoin_char_free(&str, c, 1, STRJOIN_FREE_S1)))
			return (perror_string(ERR_MEMORY));
		cstream_next(tkstream->cstream);
	}
	tkstream->cur->type = token_type_var;
	tkstream->cur->as.var.name = str;
	return (tkstream->cur);
}

void			tkstream_print_var(t_token const *const token)
{
	ft_printf("{\n\ttype: var,\n\tname: \"%s\"\n}\n", token->as.var.name);
}
