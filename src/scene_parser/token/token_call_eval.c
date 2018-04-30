/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_call_eval.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 01:53:51 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/27 13:11:33 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/interpreter.h"

static int			token_call_args_create(t_interpreter *const interpreter,
		t_token const *const tk_call, t_token **const args_eval)
{
	int			args_len;
	t_token		*cur_arg;
	t_token		tk_this;
	int			i;

	args_len = tk_call->as.call.args_len;
	if (!(*args_eval = malloc(sizeof(**args_eval) * args_len)))
		return (error_string(ERR_MEMORY));
	i = -1;
	while (++i < args_len)
	{
		cur_arg = tk_call->as.call.args[i];
		tk_this = token_class(e_class_type_none, NULL);
		if (!token_eval(interpreter, &tk_this, cur_arg, &(*args_eval)[i]))
		{
			ft_memdel((void**)args_eval);
			return (0);
		}
	}
	return (1);
}

static int			call_loop(
	t_interpreter *const interpreter, t_token *const tk_this,
	t_token const *const tk_expr, t_token *const tk_result)
{
	t_token		tk_res;
	t_token		tk_that;
	int			nb;
	int			i;

	(void)tk_this;
	*tk_result = token_class(e_class_type_none, NULL);
	if (tk_expr->as.call.args_len < 2)
		return (error_string("invalid loop call"));
	if (!token_eval(interpreter, &tk_that, tk_expr->as.call.args[0], &tk_res)
			|| tk_res.type != token_type_num)
		return (0);
	nb = tk_res.as.num.value;
	while (nb-- >= 1)
	{
		i = 0;
		while (++i < tk_expr->as.call.args_len)
		{
			tk_that = token_class(e_class_type_none, NULL);
			if (!token_eval(interpreter, &tk_that,
					tk_expr->as.call.args[i], &tk_res))
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
	t_hook_args			args;
	t_method			*method;

	if (tk_this->as.class.class_type == e_class_type_none &&
			ft_strstr(tk_expr->as.call.func, "loop"))
		return (call_loop(interpreter, tk_this, tk_expr, tk_result));
	if (!token_call_args_create(interpreter, tk_expr, &args.tokens))
		return (0);
	if (!(method = interpreter_class_type_find_method_name(
					interpreter, tk_this->as.class.class_type,
					tk_expr->as.call.func)))
	{
		ft_dprintf(STDERR_FILENO
				, "error: interpreter: undefined function: %s\n"
				, tk_expr->as.call.func);
		return (0);
	}
	args.size = tk_expr->as.call.args_len;
	args.hook_name = tk_expr->as.call.func;
	*tk_result = token_class(method->class_type, NULL);
	ret = (*method->f_hook)(interpreter, tk_this, args, tk_result);
	token_call_args_destroy(&args.tokens);
	return (ret);
}
