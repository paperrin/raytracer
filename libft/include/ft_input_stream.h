/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input_stream.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 18:03:28 by paperrin          #+#    #+#             */
/*   Updated: 2017/12/07 18:04:07 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_INPUT_STREAM_H
# define FT_INPUT_STREAM_H

# include <stddef.h>

typedef struct s_in_stream	t_in_stream;

int				ft_in_stream_next(t_in_stream *in_stream);
int				ft_in_stream_nnext(t_in_stream *in_stream,
		char *buf, size_t n);
int				ft_in_stream_peek(t_in_stream *in_stream);
size_t			ft_in_stream_available(t_in_stream *in_stream);

#endif
