/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input_stream_file.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 18:03:34 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/18 03:28:19 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_INPUT_STREAM_FILE_H
# define FT_INPUT_STREAM_FILE_H

# include "ft_input_stream.h"
# include "internal_ft_input_stream.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

# define INPUT_STREAM_FILE_BUF_SIZE 4096

typedef struct	s_in_stream_file
{
	int			fd;
	size_t		col;
	size_t		line;
}				t_in_stream_file;

int				ft_in_stream_file_open(t_in_stream *in_stream
		, const char *path);
void			ft_in_stream_file_close(t_in_stream *in_stream);

#endif
