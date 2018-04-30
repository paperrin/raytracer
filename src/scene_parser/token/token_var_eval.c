/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_var_eval.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 01:54:00 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/30 00:51:11 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/interpreter.h"

int					token_var_eval(
		t_interpreter *const interpreter, t_token *const tk_this,
		t_token const *const tk_expr, t_token *const tk_result)
{
	t_interpreter_var	*var;

	(void)tk_this;
	var = NULL;
	if (!(var = interpreter_find_var_name(interpreter, tk_expr->as.var.name)))
		return (error_string_2("unknown var", tk_expr->as.var.name));
	*tk_result = var->tk_value;
	return (1);
}
