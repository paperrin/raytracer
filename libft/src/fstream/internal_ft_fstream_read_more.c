/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal_ft_fstream_read_more.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 23:11:20 by paperrin          #+#    #+#             */
/*   Updated: 2018/03/23 23:04:55 by ilarbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fstream.h"

long			internal_ft_fstream_read_more(t_fstream *const fstream)
{
	long		n_bytes;
	size_t		new_size;

	if (fstream->read_buf_n_bytes + FT_FSTREAM_READ_SIZE
			> fstream->read_buf_size)
	{
		new_size = fstream->read_buf_n_bytes - fstream->read_offset
			+ FT_FSTREAM_READ_SIZE;
		if (!ft_memrealloc_offset((void**)&fstream->read_buf,
					fstream->read_buf_n_bytes,
					new_size, fstream->read_offset))
			return (-1);
		fstream->read_buf_n_bytes -= fstream->read_offset;
		fstream->read_offset = 0;
		fstream->read_buf_size = new_size;
	}
	if ((n_bytes = read(fstream->fd,
					&fstream->read_buf[fstream->read_buf_n_bytes],
					FT_FSTREAM_READ_SIZE)) <= 0)
		return (n_bytes);
	fstream->read_buf_n_bytes += n_bytes;
	return (n_bytes);
}
