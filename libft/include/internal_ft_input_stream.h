/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal_ft_input_stream.h                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/07 18:03:39 by paperrin          #+#    #+#             */
/*   Updated: 2017/12/07 18:04:56 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERNAL_FT_INPUT_STREAM_H
# define INTERNAL_FT_INPUT_STREAM_H

# include <stddef.h>

struct				s_in_stream
{
	char			*buf;
	int				current;
	size_t			pos;
	size_t			available;
	int				(*f_next)(struct s_in_stream*);
	void			*in_source;
};

#endif
