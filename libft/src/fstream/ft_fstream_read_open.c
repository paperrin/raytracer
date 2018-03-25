/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fstream_read_open.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 20:26:59 by paperrin          #+#    #+#             */
/*   Updated: 2018/03/24 21:58:04 by ilarbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_fstream.h"

t_fstream		*ft_fstream_read_open(char const *const path)
{
	t_fstream		*fstream;

	if (!(fstream = (t_fstream*)malloc(sizeof(*fstream))))
		return (NULL);
	if ((fstream->fd = open(path, O_RDONLY)) < 0)
	{
		free(fstream);
		return (NULL);
	}
	fstream->read_buf = NULL;
	fstream->read_offset = 0;
	fstream->read_buf_n_bytes = 0;
	fstream->read_buf_size = 0;
	return (fstream);
}

void			ft_fstream_close(t_fstream **fstream)
{
	if (fstream && *fstream)
	{
		if ((*fstream)->read_buf)
			ft_memdel((void**)&((*fstream)->read_buf));
		if ((*fstream)->fd >= 0)
		{
			close((*fstream)->fd);
			(*fstream)->fd = -1;
		}
		ft_memdel((void**)fstream);
	}
}
