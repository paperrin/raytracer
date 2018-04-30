/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstream.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 16:23:31 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/09 16:52:27 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CSTREAM_H
# define CSTREAM_H

# include "rt.h"
# include "ft_fstream.h"
# include "ft_printf.h"

typedef struct		s_char_stream
{
	char			*file_path;
	t_fstream		*fstream;
	unsigned int	line;
	unsigned int	col;
}					t_char_stream;

t_char_stream		*cstream_open(char const *const file_path);
void				cstream_close(t_char_stream **cstream);
char				cstream_next(t_char_stream *const cstream);
char				cstream_peek(t_char_stream *const cstream);
int					cstream_error(t_char_stream const *const cstream,
		char const *const error);
void				cstream_skip_chars(t_char_stream *const cstream,
		char const *const chars);
void				cstream_skip_to_chars(t_char_stream *const cstream,
		char const *const chars);
void				cstream_skip_whitespaces(t_char_stream *const cstream);

#endif
