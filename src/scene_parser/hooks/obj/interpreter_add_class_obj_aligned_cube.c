/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_add_class_obj_aligned_cube.c           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarbi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 19:27:24 by ilarbi            #+#    #+#             */
/*   Updated: 2018/04/27 17:09:01 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/hooks.h"
#include "./internal_obj_methods.h"

static int	f_class_aligned_cube(t_interpreter *const interpreter,
		t_token *const tk_this, t_hook_args const args,
		t_token *const tk_return)
{
	t_obj	*obj;

	(void)tk_this;
	if (!hook_valid_args(&args, 0))
		return (0);
	if (!(obj = scene_add_aligned_cube(&interpreter->app->scene, NULL)))
		return (0);
	tk_return->as.class.ptr = (void*)obj;
	return (1);
}

static int	f_method_size(t_interpreter *const interpreter,
		t_token *const tk_this, t_hook_args const args,
		t_token *const tk_return)
{
	t_obj	*obj;

	(void)tk_this;
	(void)interpreter;
	obj = (t_obj*)tk_this->as.class.ptr;
	if (hook_args_match(&args, 3,
		token_type_num, token_type_num, token_type_num))
	{
		obj->as.aligned_cube.size = vec3r(
				fabs(args.tokens[0].as.num.value),
				fabs(args.tokens[1].as.num.value),
				fabs(args.tokens[2].as.num.value));
	}
	else if (hook_args_match(&args, 1, token_type_num))
	{
		obj->as.aligned_cube.size = vec3r(
				fabs(args.tokens[0].as.num.value),
				fabs(args.tokens[0].as.num.value),
				fabs(args.tokens[0].as.num.value));
	}
	else
		return (hook_error(&args, "invalid args"));
	*tk_return = *tk_this;
	return (1);
}

int			interpreter_add_class_obj_aligned_cube(
		t_interpreter *const interpreter)
{
	const t_e_class_type	class_type = e_class_type_obj_aligned_cube;

	if (!interpreter_class_add(interpreter, class_type,
		interpreter_method_create("ObjAlignedCube", &f_class_aligned_cube)))
		return (0);
	if (!interpreter_class_add_method_batch(interpreter, class_type, 3,
		"size", &f_method_size,
		"material", &f_internal_obj_method_material,
		"pos", &f_internal_obj_method_pos))
		return (0);
	return (1);
}
