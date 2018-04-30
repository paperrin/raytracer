/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkstream_dispose.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 19:42:54 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/09 16:59:53 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/tkstream.h"

void		tkstream_dispose(t_token_stream *const tkstream)
{
	if (tkstream->cur)
		token_destroy(&tkstream->cur);
}
