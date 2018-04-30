/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fstream_sread_next_char.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 17:02:23 by paperrin          #+#    #+#             */
/*   Updated: 2018/02/17 17:55:07 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fstream.h"

int			ft_fstream_speek_char(t_fstream *const fstream)
{
	long		bytes_read;

	if (!fstream->read_buf
			|| fstream->read_buf_n_bytes - fstream->read_offset <= 0)
	{
		if ((bytes_read = internal_ft_fstream_read_more(fstream)) <= 0)
			return (bytes_read - 1);
	}
	return (fstream->read_buf[fstream->read_offset]);
}

int			ft_fstream_sread_char(t_fstream *const fstream)
{
	int		ret;

	ret = ft_fstream_speek_char(fstream);
	fstream->read_offset++;
	return (ret);
}
