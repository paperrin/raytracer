/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkstream.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 16:18:28 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/11 20:20:14 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TKSTREAM_H
# define TKSTREAM_H

# include "scene_parser/cstream.h"
# include "scene_parser/token.h"

# define TKSTREAM_NB_ESC_CODES 5

typedef struct s_token_stream		t_token_stream;

typedef t_token	*(t_f_token_read)(t_token_stream *const);

struct				s_token_stream
{
	t_token			*cur;
	t_char_stream	*cstream;
	unsigned int	line;
	unsigned int	col;
	int				did_error;
};

t_token_stream		*tkstream_open(char const *const file_path);
void				tkstream_close(t_token_stream **tkstream);

t_token				*tkstream_next(t_token_stream *const tkstream);
t_token				*tkstream_peek(t_token_stream *const tkstream);
t_token				*tkstream_read_token(t_token_stream *const tkstream);
t_token				*tkstream_read_punc(t_token_stream *const tkstream);
t_token				*tkstream_read_op(t_token_stream *const tkstream);
t_token				*tkstream_read_str(t_token_stream *const tkstream);
t_token				*tkstream_read_num(t_token_stream *const tkstream);
t_token				*tkstream_read_var(t_token_stream *const tkstream);

int					tkstream_error(t_token_stream *const tkstream,
		char const *const error);
void				*tkstream_perror(t_token_stream *const tkstream,
		char const *const error);
int					tkstream_ferror(t_token_stream *const tkstream,
		char const *const error);
void				*tkstream_pferror(t_token_stream *const tkstream,
		char const *const error);

#endif
