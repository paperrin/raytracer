/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input_stream_file.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 18:08:28 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/18 03:39:29 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_input_stream_file.h"
#include "internal_ft_input_stream.h"

static int	read_to_buf(t_in_stream *in_stream)
{
	t_in_stream_file	*file;
	int					count;

	file = (t_in_stream_file*)in_stream->in_source;
	count = read(file->fd, in_stream->buf, INPUT_STREAM_FILE_BUF_SIZE);
	in_stream->pos = 0;
	if (count > 0)
		in_stream->current = in_stream->buf[0];
	else
	{
		in_stream->current = count - 1;
		in_stream->available = 0;
		return (in_stream->current);
	}
	in_stream->available = count;
	return (1);
}

static int	f_next(t_in_stream *in_stream)
{
	t_in_stream_file	*file;

	if (in_stream->pos >= in_stream->available)
	{
		if (read_to_buf(in_stream) < 0)
			return (in_stream->current);
	}
	file = (t_in_stream_file*)in_stream->in_source;
	in_stream->current = in_stream->buf[in_stream->pos];
	if (in_stream->current == '\n')
	{
		file->col = 0;
		file->line++;
	}
	else
		file->col++;
	in_stream->pos++;
	return (in_stream->current);
}

static int	alloc_stream_buffer(t_in_stream *in_stream)
{
	if (!(in_stream->buf = (char*)malloc(sizeof(*in_stream->buf)
					* INPUT_STREAM_FILE_BUF_SIZE)))
	{
		close(((t_in_stream_file*)in_stream->in_source)->fd);
		ft_memdel(&in_stream->in_source);
		return (0);
	}
	return (1);
}

int			ft_in_stream_file_open(t_in_stream *in_stream, const char *path)
{
	if (!(in_stream->in_source = (void*)malloc(sizeof(t_in_stream_file))))
		return (0);
	if ((((t_in_stream_file*)in_stream->in_source)->fd = open(path, O_RDONLY))
			< 0)
	{
		ft_memdel(&in_stream->in_source);
		return (0);
	}
	if (!alloc_stream_buffer(in_stream))
		return (0);
	in_stream->pos = 0;
	in_stream->available = 0;
	in_stream->f_next = &f_next;
	((t_in_stream_file*)in_stream->in_source)->line = 1;
	((t_in_stream_file*)in_stream->in_source)->col = 1;
	if (read_to_buf(in_stream) < -1)
	{
		ft_in_stream_file_close(in_stream);
		return (0);
	}
	return (1);
}

void		ft_in_stream_file_close(t_in_stream *in_stream)
{
	t_in_stream_file	*file;

	file = (t_in_stream_file*)in_stream->in_source;
	if (file)
	{
		close(file->fd);
		if (in_stream->buf)
			free(in_stream->buf);
		free(file);
		in_stream->in_source = NULL;
	}
}
