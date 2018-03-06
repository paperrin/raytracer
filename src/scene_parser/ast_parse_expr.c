/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parse_expr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 19:31:56 by paperrin          #+#    #+#             */
/*   Updated: 2018/03/06 22:39:30 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser.h"

t_token			*ast_parse_expr(t_token_stream *const tkstream)
{
	t_token		*tk;

	tk = tkstream_peek(tkstream);
	tkstream_next(tkstream);
	return (tk);
}
