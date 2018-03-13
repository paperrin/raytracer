/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkstream_dispose.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 19:42:54 by paperrin          #+#    #+#             */
/*   Updated: 2018/03/06 19:44:32 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser.h"

void		tkstream_dispose(t_token_stream *const tkstream)
{
	if (tkstream->cur)
		token_destroy(&tkstream->cur);
}
