/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_op_eval.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 01:53:59 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/10 01:05:25 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/interpreter.h"

int					token_op_eval(t_interpreter *const interpreter,
		t_token const *const tk_expr, t_token *const tk_result)
{
	(void)interpreter;

	*tk_result = *tk_expr;
	return (1);
}
