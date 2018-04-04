/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parse_expr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 19:31:56 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/04 22:27:45 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser.h"

static t_token		*handle_operand(t_token_stream *const tkstream,
		t_token *tk)
{
	if (!tk)
		return (NULL);
	if (tk->type != token_type_op)
		return (tk);
	if (tk->as.op.value != '+' && tk->as.op.value != '-')
	{
		token_destroy(&tk);
		tkstream_error(tkstream, "unexpected operator");
		return (NULL);
	}
	if (!(tk->as.op.left = token_num(0)))
	{
		token_destroy(&tk);
		return (perror_string(ERR_MEMORY));
	}
	if (!(tk->as.op.right = ast_parse_maybe_call(tkstream)))
		token_destroy(&tk);
	else if (tk->as.op.right->type != token_type_num)
	{
		token_destroy(&tk);
		tkstream_error(tkstream, "unexpected token after operator");
	}
	return (tk);
}

static t_token		*handle_op(t_token_stream *const tkstream, t_token *tk_left,
		t_token *tk_op)
{
	tk_op->as.op.left = tk_left;
	if (!(tk_op->as.op.right = handle_operand(tkstream,
					ast_parse_maybe_call(tkstream))))
	{
		token_destroy(&tk_op);
		return (NULL);
	}
	return (tk_op);
}

static t_token		*recursive_parse_expr(t_token_stream *const tkstream,
		t_token **tk_left)
{
	t_token		*tk_op;
	t_token		*tk_next;

	if (!*tk_left && !(*tk_left = handle_operand(
					tkstream, ast_parse_maybe_call(tkstream))))
		return (NULL);
	if (!(tk_op = tkstream_peek(tkstream)))
		return (*tk_left);
	else if (tk_op->type == token_type_op)
	{
		tkstream_next(tkstream);
		if (!(tk_op = handle_op(tkstream, *tk_left, tk_op)))
			return (NULL);
		if (!(tk_next = tkstream_peek(tkstream)))
			return (tk_op);
		else if (tk_next->type == token_type_op)
			return (recursive_parse_expr(tkstream, &tk_op));
		return (tk_op);
	}
	return (*tk_left);
}

t_token				*ast_parse_expr(t_token_stream *const tkstream)
{
	t_token		*token;

	token = NULL;
	return (recursive_parse_expr(tkstream, &token));
}
