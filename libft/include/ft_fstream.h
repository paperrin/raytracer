/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fstream.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 20:27:32 by paperrin          #+#    #+#             */
/*   Updated: 2018/03/22 22:49:39 by ilarbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FSTREAM_H
# define FT_FSTREAM_H

# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

# define FT_FSTREAM_READ_SIZE 4096

typedef struct			s_fstream
{
	int					fd;
	char				*read_buf;
	size_t				read_offset;
	size_t				read_buf_n_bytes;
	size_t				read_buf_size;
}						t_fstream;

t_fstream		*ft_fstream_read_open(char const *const path);
void			ft_fstream_close(t_fstream **fstream);

/*
** @param chars - must contain at least one character before
** the terminating \0 (which can be a contained \0)
*/
long			ft_fstream_sread_to_any_char(t_fstream *const fstream,
		char **line, char const *const chars, int is_included);
long			ft_fstream_bread_n_bytes(t_fstream *const fstream,
		char **bytes, size_t n_bytes);

/*
** !INTERNAL
** Reads more bytes from associated fd without updating read_offset
** used in other read functions
*/
long			internal_ft_fstream_read_more(t_fstream *const fstream);

#endif
