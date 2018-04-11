/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_op_eval.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 01:53:59 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/11 20:16:24 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/interpreter.h"

static float		float_do_op(char op, float left, float right)
{
	if (op == '+')
		return (left + right);
	else if (op == '-')
		return (left - right);
	else if (op == '*')
		return (left * right);
	else if (op == '/')
		return (left / right);
	return (0);
}

static int			token_do_op(char op, t_token const *const tk_left,
		t_token const *const tk_right, t_token *const tk_result)
{
	if (tk_left->type != token_type_num || tk_right->type != token_type_num)
		return (error_string("interpreter: unsupported operand"));
	if (!ft_strchr("+-*/", op))
		return (error_string("interpreter: unsupported operator"));
	tk_result->type = token_type_num;
	tk_result->as.num.value = float_do_op(
			op, tk_left->as.num.value, tk_right->as.num.value);
	return (1);
}

int					token_op_eval(
		t_interpreter *const interpreter, t_token *const tk_this,
		t_token const *const tk_expr, t_token *const tk_result)
{
	t_token		tk_left_eval;
	t_token		tk_right_eval;

	if (!token_eval(interpreter, tk_this, tk_expr->as.op.left, &tk_left_eval))
		return (0);
	if (tk_expr->as.op.value == '.')
		*tk_this = tk_left_eval;
	if (!token_eval(interpreter, tk_this, tk_expr->as.op.right, &tk_right_eval))
		return (0);
	if (tk_expr->as.op.value != '.')
	{
		if (!token_do_op(tk_expr->as.op.value,
				&tk_left_eval, &tk_right_eval, tk_result))
			return (0);
	}
	else
	{
		*tk_result = tk_right_eval;
		*tk_this = tk_right_eval;
	}
	return (1);
}
