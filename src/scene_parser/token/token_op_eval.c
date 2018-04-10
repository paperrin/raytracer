/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_op_eval.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 01:53:59 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/10 23:30:30 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/interpreter.h"

int					token_op_eval(
		t_interpreter *const interpreter, t_token *const tk_this,
		t_token const *const tk_expr, t_token *const tk_result)
{
	tk_this->as.class.class_type = e_class_type_none;
	tk_this->as.class.ptr = NULL;
	if (!token_eval(interpreter, tk_this, tk_expr->as.op.left, tk_result))
		return (0);
	if (tk_expr->as.op.value == '.')
		*tk_this = *tk_result;
	if (!token_eval(interpreter, tk_this, tk_expr->as.op.right, tk_result))
		return (0);
	return (1);
}
