/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstream.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 18:22:36 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/09 16:34:25 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/cstream.h"

t_char_stream		*cstream_open(char const *const file_path)
{
	t_char_stream		*cstream;

	cstream = NULL;
	if (!(cstream = (t_char_stream*)malloc(sizeof(*cstream)))
			|| !(cstream->file_path = ft_strdup(file_path)))
	{
		if (cstream)
			free(cstream);
		return (perror_string(ERR_MEMORY));
	}
	if (!(cstream->fstream = ft_fstream_read_open(file_path)))
	{
		free(cstream->file_path);
		free(cstream);
		ft_dprintf(STDERR_FILENO,
				"error: could not open file \"%s\"\n", file_path);
		return (NULL);
	}
	cstream->line = 1;
	cstream->col = 1;
	return (cstream);
}

void				cstream_close(t_char_stream **cstream)
{
	ft_fstream_close(&(*cstream)->fstream);
	free((*cstream)->file_path);
	ft_memdel((void**)cstream);
}

char				cstream_next(t_char_stream *const cstream)
{
	int		c;

	if ((c = ft_fstream_sread_char(cstream->fstream)) <= 0)
		return ('\0');
	cstream->col++;
	if (c == '\n')
	{
		cstream->line++;
		cstream->col = 1;
	}
	return (c);
}

char				cstream_peek(t_char_stream *const cstream)
{
	int		c;

	if ((c = ft_fstream_speek_char(cstream->fstream)) <= 0)
		return ('\0');
	return (c);
}

int					cstream_error(t_char_stream const *const cstream,
		char const *const error)
{
	ft_dprintf(STDERR_FILENO, "%s:%u:%u: error: %s\n", cstream->file_path,
			cstream->line, cstream->col, error);
	return (0);
}
