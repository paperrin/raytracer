/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_parse_expr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 19:31:56 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/21 06:31:33 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/ast.h"

static t_token		*handle_operand_sign(t_token_stream *const tkstream,
		t_token *tk)
{
	if (!tk || tk->type != token_type_op)
		return (tk);
	if (!ft_strchr("+-", tk->as.op.value))
	{
		token_destroy(&tk);
		return (tkstream_perror(tkstream, "unexpected operator"));
	}
	if (!(tk->as.op.left = token_num_alloc(0)))
	{
		token_destroy(&tk);
		return (tkstream_perror(tkstream, ERR_MEMORY));
	}
	if (!(tk->as.op.right = ast_parse_maybe_call(tkstream)))
		token_destroy(&tk);
	else if (tk->as.op.right->type != token_type_num)
	{
		token_destroy(&tk);
		return (tkstream_perror(tkstream, "unexpected token after operator"));
	}
	return (tk);
}

static int			get_precedence(char op)
{
	static char		precedence[OPERATOR_PRECEDENCE_NB_OPS * 2] = {
		'+', 1,
		'-', 1,
		'*', 2,
		'/', 2,
		'.', 3};
	int				i;

	i = -1;
	while (++i < OPERATOR_PRECEDENCE_NB_OPS)
	{
		if (precedence[i * 2] == op)
			return ((int)precedence[i * 2 + 1]);
	}
	return (-1);
}

static t_token		*handle_op(t_token_stream *const tkstream,
		t_token *tk_left, t_token *tk_op)
{
	t_token		*tk_right;

	if (!tkstream_next(tkstream))
		return (tkstream_pferror(tkstream, "dangling operator"));
	if (!(tk_right = handle_operand_sign(tkstream,
					ast_parse_maybe_call(tkstream))))
		return (NULL);
	if (tk_left->type == token_type_op
			&& (get_precedence(tk_left->as.op.value)
				< get_precedence(tk_op->as.op.value)))
	{
		tk_op->as.op.left = tk_left->as.op.right;
		tk_op->as.op.right = tk_right;
		tk_left->as.op.right = tk_op;
		return (tk_left);
	}
	else
	{
		tk_op->as.op.left = tk_left;
		tk_op->as.op.right = tk_right;
		return (tk_op);
	}
}

static t_token		*recursive_parse_expr(t_token_stream *const tkstream,
		t_token **tk_left)
{
	t_token		*tk_op;
	t_token		*tk_next;

	if (!*tk_left && !(*tk_left = handle_operand_sign(
					tkstream, ast_parse_maybe_call(tkstream))))
		return (NULL);
	if (!(tk_op = tkstream_peek(tkstream)))
		return (*tk_left);
	else if (tk_op->type == token_type_op)
	{
		if (!(tk_op = handle_op(tkstream, *tk_left, tk_op)))
		{
			token_destroy(&tk_op);
			return (NULL);
		}
		if ((tk_next = tkstream_peek(tkstream))
				&& tk_next->type == token_type_op)
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
