/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_op_eval.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 23:41:20 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/30 02:11:19 by paperrin         ###   ########.fr       */
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

static int			token_do_str_concat(t_token const *const tk_left,
		t_token const *const tk_right, t_token *const tk_result)
{
	char		*num;
	char		*s;

	tk_result->as.str.value = NULL;
	if (!(num = ft_itoa(tk_right->as.num.value)))
		return (error_string(ERR_MEMORY));
	if (!(s = ft_strjoin_free(
			(char**)&tk_left->as.str.value, &num, STRJOIN_FREE_S2)))
	{
		ft_memdel((void**)&num);
		return (error_string(ERR_MEMORY));
	}
	ft_memdel((void**)&num);
	tk_result->type = token_type_str;
	tk_result->as.str.value = s;
	return (1);
}

static int			token_do_op_string(
		t_interpreter *const interpreter,
		t_token const *const tk_left, t_token const *const tk_right,
		t_token *const tk_result)
{
	char		**new_str_concat;

	if (tk_left->type != token_type_str || tk_right->type != token_type_num)
		return (0);
	if (!token_do_str_concat(tk_left, tk_right, tk_result))
		return (-1);
	if (!(new_str_concat = ft_vector_push_back(&interpreter->v_string_concats
					, NULL)))
	{
		ft_memdel((void**)&tk_result->as.str.value);
		return (error_string(ERR_MEMORY) - 1);
	}
	*new_str_concat = tk_result->as.str.value;
	return (1);
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
	int			is_concat;

	is_concat = 0;
	if (!token_eval(interpreter, tk_this, tk_expr->as.op.left, &tk_left_eval))
		return (0);
	if (tk_expr->as.op.value == '.')
		*tk_this = tk_left_eval;
	if (!token_eval(interpreter, tk_this, tk_expr->as.op.right, &tk_right_eval))
		return (0);
	if (tk_expr->as.op.value != '.')
	{
		if (tk_expr->as.op.value == '+' && (is_concat = token_do_op_string(
				interpreter, &tk_left_eval, &tk_right_eval, tk_result)) < 0)
			return (0);
		if (!is_concat && !token_do_op(tk_expr->as.op.value,
				&tk_left_eval, &tk_right_eval, tk_result))
			return (0);
	}
	if (tk_expr->as.op.value == '.')
		*tk_result = tk_right_eval;
	if (tk_expr->as.op.value == '.')
		*tk_this = tk_right_eval;
	return (1);
}
