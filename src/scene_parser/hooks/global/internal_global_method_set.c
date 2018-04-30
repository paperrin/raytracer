/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal_global_method_set.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 03:58:10 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/30 20:27:15 by tlernoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/hooks.h"
#include "./internal_global_methods.h"

int				f_internal_global_method_set(
		t_interpreter *const interpreter,
		t_token *const tk_this, t_hook_args const args,
		t_token *const tk_return)
{
	char					*var_name;
	t_interpreter_var		*var;

	*tk_return = *tk_this;
	if (!hook_valid_args(&args, 2, token_type_str, token_type_num))
		return (0);
	var_name = args.tokens[0].as.str.value;
	if ((var = interpreter_find_var_name(interpreter, var_name)))
	{
		if (var->is_constant)
			return (hook_error_str(&args, "can't set constant var", var_name));
		token_content_destroy(&var->tk_value);
		var->tk_value = args.tokens[1];
	}
	else if (!interpreter_var_add(interpreter, var_name, args.tokens[1]))
		return (0);
	return (1);
}

int				f_internal_global_method_rand(
		t_interpreter *const interpreter,
		t_token *const tk_this, t_hook_args const args,
		t_token *const tk_return)
{
	(void)interpreter;
	*tk_return = *tk_this;
	if (!hook_valid_args(&args, 0))
		return (0);
	*tk_return = token_num((float)rand() / (float)RAND_MAX);
	return (1);
}

int				f_internal_global_method_rand_int(
		t_interpreter *const interpreter,
		t_token *const tk_this, t_hook_args const args,
		t_token *const tk_return)
{
	(void)interpreter;
	*tk_return = *tk_this;
	if (!hook_valid_args(&args, 1, token_type_num))
		return (0);
	*tk_return = token_num(rand() % (int)args.tokens[0].as.num.value);
	return (1);
}
