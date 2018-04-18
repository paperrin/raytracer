/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fstream_sread_to_any_char.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 23:37:51 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/18 03:30:04 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fstream.h"

static long		search_get_offset(t_fstream const *const fstream,
		char const *const chars, size_t read_offset)
{
	char		*found;
	size_t		n_chars;
	long		found_offset;

	found_offset = -1;
	n_chars = ft_strlen(&chars[!*chars]) + !*chars;
	if ((found = (char*)ft_memchr_any(
				(void*)&fstream->read_buf[fstream->read_offset + read_offset],
				fstream->read_buf_n_bytes - fstream->read_offset - read_offset,
				(void*)chars, n_chars)))
		found_offset = found - fstream->read_buf;
	return (found_offset);
}

static long		found_to_line(t_fstream *const fstream, char **line, long found)
{
	size_t		len;

	len = found - fstream->read_offset;
	if (!(*line = (char*)malloc(sizeof(char) * (len + 1))))
		return (-1);
	ft_memcpy(*line, &fstream->read_buf[fstream->read_offset], len);
	(*line)[len] = '\0';
	fstream->read_offset = found;
	return (len);
}

long			ft_fstream_sread_to_any_char(t_fstream *const fstream,
		char **line, char const *const chars, int is_included)
{
	long		n_new_bytes;
	size_t		read_offset;
	long		found;

	read_offset = 0;
	found = -1;
	if (fstream->read_buf)
	{
		found = search_get_offset(fstream, chars, read_offset);
		read_offset += fstream->read_buf_n_bytes - fstream->read_offset;
	}
	n_new_bytes = 0;
	while (found < 0
			&& (n_new_bytes = internal_ft_fstream_read_more(fstream)) > 0)
	{
		if ((found = search_get_offset(fstream, chars, read_offset)) > -1)
			break ;
		read_offset += fstream->read_buf_n_bytes - fstream->read_offset;
	}
	if (n_new_bytes < 0)
		return (n_new_bytes);
	found = (found < 0) ? fstream->read_buf_n_bytes
		: found + (is_included != 0);
	return (found_to_line(fstream, line, found));
}
