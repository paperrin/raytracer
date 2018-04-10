/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_call_eval.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 01:53:51 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/10 23:26:08 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/interpreter.h"

static int			token_call_args_create(t_interpreter *const interpreter,
		t_token const *const tk_call, t_token **const args_eval)
{
	int			args_len;
	t_token		*cur_arg;
	int			i;

	args_len = tk_call->as.call.args_len;
	if (!(*args_eval = malloc(sizeof(**args_eval) * args_len)))
		return (error_string(ERR_MEMORY));
	i = -1;
	while (++i < args_len)
	{
		cur_arg = tk_call->as.call.args[i];
		if (!token_eval(interpreter, NULL, cur_arg, args_eval[i]))
		{
			ft_memdel((void**)args_eval);
			return (0);
		}
	}
	return (1);
}

static void			token_call_args_destroy(t_token **args_eval)
{
	ft_memdel((void**)args_eval);
}

int					token_call_eval(
		t_interpreter *const interpreter, t_token *const tk_this,
		t_token const *const tk_expr, t_token *const tk_result)
{
	int					ret;
	t_token				*args_eval;
	t_method			*method;

	if (!token_call_args_create(interpreter, tk_expr, &args_eval))
		return (0);
	if (!(method = interpreter_class_type_find_method_name(
					interpreter, tk_this->as.class.class_type,
					tk_expr->as.call.func)))
		return (0);
	ret = (*method->f_hook)(tk_this, args_eval,
			tk_expr->as.call.args_len, tk_result);
	token_call_args_destroy(&args_eval);
	return (ret);
}
