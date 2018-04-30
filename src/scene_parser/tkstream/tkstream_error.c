/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkstream_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 16:35:08 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/09 16:59:53 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/tkstream.h"

int					tkstream_ferror(t_token_stream *const tkstream,
		char const *const error)
{
	tkstream->did_error = 1;
	if (error)
	{
		ft_dprintf(STDERR_FILENO, "%s:%u:%u: error: %s\n",
				tkstream->cstream->file_path,
				tkstream->line, tkstream->col, error);
	}
	return (0);
}

void				*tkstream_pferror(t_token_stream *const tkstream,
		char const *const error)
{
	tkstream_ferror(tkstream, error);
	return (NULL);
}

int					tkstream_error(t_token_stream *const tkstream,
		char const *const error)
{
	tkstream->did_error = 1;
	if (error)
		error_string(error);
	return (0);
}

void				*tkstream_perror(t_token_stream *const tkstream,
		char const *const error)
{
	tkstream->did_error = 1;
	if (error)
		error_string(error);
	return (NULL);
}
