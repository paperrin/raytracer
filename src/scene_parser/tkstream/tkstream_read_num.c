/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkstream_read_num.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/04 21:21:52 by paperrin          #+#    #+#             */
/*   Updated: 2018/03/23 23:56:16 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser.h"

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
			return (perror_string(ERR_MEMORY));
		cstream_next(tkstream->cstream);
	}
	tkstream->cur->type = token_type_num;
	tkstream->cur->as.num.value = ft_atof(str, '.');
	ft_strdel(&str);
	return (tkstream->cur);
}

void			tkstream_print_num(t_token const *const token)
{
	char		*value;

	value = ft_ftoa(token->as.num.value, 5, ".");
	ft_printf("{\n\ttype: num,\n\tvalue: \"");
	if (value)
	{
		ft_printf("%s\"\n}\n", value);
		free(value);
	}
	else
		ft_printf("error");
}
