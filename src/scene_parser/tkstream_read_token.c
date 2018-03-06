/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tkstream_read_token.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 18:57:19 by paperrin          #+#    #+#             */
/*   Updated: 2018/03/05 18:23:57 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser.h"

static void		tkstream_read_comment(t_token_stream const* tkstream)
{
	while (cstream_peek(tkstream->cstream) == '#')
	{
		cstream_skip_to_chars(tkstream->cstream, "\n\r");
		cstream_skip_whitespaces(tkstream->cstream);
	}
}

static t_token	*read_token(t_token_stream *const tkstream, int *is_unsupported)
{
	static void			*f_tokens[TKSTREAM_NB_F_TOKENS * 2] = {
		(void*)",()", (void*)&tkstream_read_punc,
		(void*)"\"", (void*)&tkstream_read_str,
		(void*)"0123456789", (void*)&tkstream_read_num,
		(void*)".-+/*", (void*)&tkstream_read_op,
		(void*)"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ",
			(void*)&tkstream_read_var};
	int					i;

	i = -1;
	*is_unsupported = 0;
	while (++i < TKSTREAM_NB_F_TOKENS && tkstream->cur)
	{
		if (ft_strchr((char*)f_tokens[i * 2], cstream_peek(tkstream->cstream)))
		{
			if (!(((t_f_token_read*)f_tokens[i * 2 + 1])(tkstream)))
				ft_memdel((void**)&tkstream->cur);
			else
				return (tkstream->cur);
		}
	}
	*is_unsupported = (i == TKSTREAM_NB_F_TOKENS && tkstream->cur);
	return (NULL);
}

t_token			*tkstream_read_token(t_token_stream *const tkstream)
{
	int			is_unsupported;

	tkstream_read_comment(tkstream);
	if (!(tkstream->cur = (t_token*)malloc(sizeof(*tkstream->cur))))
		return (perror_string(ERR_MEMORY));
	tkstream->col = tkstream->cstream->col;
	tkstream->line = tkstream->cstream->line;
	if (!read_token(tkstream, &is_unsupported))
	{
		if (is_unsupported)
			cstream_error(tkstream->cstream, "unknown token");
		return (NULL);
	}
	return (tkstream->cur);
}

void			tkstream_print_token(t_token const *const token)
{
	static void			*f_print_tokens[TKSTREAM_NB_F_TOKENS * 2] = {
		(void*)token_type_punc, (void*)&tkstream_print_punc,
		(void*)token_type_str, (void*)&tkstream_print_str,
		(void*)token_type_num, (void*)&tkstream_print_num,
		(void*)token_type_op, (void*)&tkstream_print_op,
		(void*)token_type_var, (void*)&tkstream_print_var};
	int					i;

	i = -1;
	while (++i < TKSTREAM_NB_F_TOKENS)
	{
		if (token->type == (unsigned int)f_print_tokens[i * 2])
		{
			((t_f_token_print*)f_print_tokens[i * 2 + 1])(token);
			return ;
		}
	}
	ft_printf("{null}\n");
}
