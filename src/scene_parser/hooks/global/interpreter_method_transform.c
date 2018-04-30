/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_method_transform.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 16:55:11 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/30 18:33:01 by tlernoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/hooks.h"
#include "./internal_global_methods.h"

static int		f_method_translate(
		t_interpreter *const interpreter,
		t_token *const tk_this, t_hook_args const args,
		t_token *const tk_return)
{
	*tk_return = *tk_this;
	if (!hook_valid_args(&args, 3
				, token_type_num, token_type_num, token_type_num))
		return (0);
	scene_translate(&interpreter->app->scene
			, args.tokens[0].as.num.value
			, args.tokens[1].as.num.value
			, args.tokens[2].as.num.value);
	return (1);
}

static int		f_method_rotate(
		t_interpreter *const interpreter,
		t_token *const tk_this, t_hook_args const args,
		t_token *const tk_return)
{
	*tk_return = *tk_this;
	if (!hook_valid_args(&args, 3
				, token_type_num, token_type_num, token_type_num))
		return (0);
	scene_rotate(&interpreter->app->scene
			, args.tokens[0].as.num.value / 180. * M_PI
			, args.tokens[1].as.num.value / 180. * M_PI
			, args.tokens[2].as.num.value / 180. * M_PI);
	return (1);
}

static int		f_method_push(
		t_interpreter *const interpreter,
		t_token *const tk_this, t_hook_args const args,
		t_token *const tk_return)
{
	*tk_return = *tk_this;
	if (!hook_valid_args(&args, 0))
		return (0);
	if (!scene_transform_push(&interpreter->app->scene))
		return (0);
	return (1);
}

static int		f_method_pop(
		t_interpreter *const interpreter,
		t_token *const tk_this, t_hook_args const args,
		t_token *const tk_return)
{
	*tk_return = *tk_this;
	if (!hook_valid_args(&args, 0))
		return (0);
	scene_transform_pop(&interpreter->app->scene);
	return (1);
}

int				interpreter_add_hooks_transform(
		t_interpreter *const interpreter)
{
	const t_e_class_type		class_type = e_class_type_none;

	if (!(interpreter_class_add_method_batch(interpreter, class_type, 7,
					"translate", &f_method_translate,
					"rotate", &f_method_rotate,
					"push", &f_method_push,
					"pop", &f_method_pop,
					"set", &f_internal_global_method_set,
					"rand", &f_internal_global_method_rand,
					"randInt", &f_internal_global_method_rand_int)))
		return (0);
	return (1);
}
