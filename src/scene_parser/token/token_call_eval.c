/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_call_eval.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 01:53:51 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/10 02:26:15 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/interpreter.h"

int					token_call_eval(t_interpreter *const interpreter,
		t_token const *const tk_expr, t_token *const tk_result)
{
	t_method			*method;

	if (!(method = interpreter_method_find_name(interpreter, e_class_type_none, "print")))
		return (0);
	(*method->f_hook)(NULL, tk_expr->as.call.args[0], 1, tk_result);
	return (1);
}
