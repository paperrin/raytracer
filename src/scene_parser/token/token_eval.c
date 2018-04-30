/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_eval.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 01:37:05 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/19 00:42:46 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/interpreter.h"

int			token_eval(t_interpreter *const interpreter, t_token *const tk_this,
		t_token const *const tk_expr, t_token *const tk_result)
{
	static const void *const	f_token_eval[TOKEN_EVAL_NB_F_TOKENS * 2] = {
		(void*)token_type_op, (void*)&token_op_eval,
		(void*)token_type_var, (void*)&token_var_eval,
		(void*)token_type_call, (void*)&token_call_eval};
	int							i;

	i = -1;
	while (++i < TOKEN_EVAL_NB_F_TOKENS)
	{
		if (tk_expr->type != (t_e_token_type)f_token_eval[i * 2])
			continue ;
		if (!((t_f_token_eval*)f_token_eval[i * 2 + 1])(
					interpreter, tk_this, tk_expr, tk_result))
			return (0);
		return (1);
	}
	*tk_result = *tk_expr;
	return (1);
}
