/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_add_class_material.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 23:47:16 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/19 00:54:47 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/hooks.h"
#include "./internal_material_methods.h"

static int	f_class_material(t_interpreter *const interpreter,
		t_token *const tk_this, t_hook_args const args,
		t_token *const tk_return)
{
	t_material		*material;

	(void)interpreter;
	(void)tk_this;
	if (!hook_valid_args(&args, 1, token_type_str))
		return (0);
	if (!(material = scene_add_material(&interpreter->app->scene
					, args.tokens[0].as.str.value)))
		return (0);
	tk_return->as.class.ptr = (void*)material;
	return (1);
}

int			interpreter_add_class_material(t_interpreter *const interpreter)
{
	const t_e_class_type		class_type = e_class_type_material;

	if (!interpreter_class_add(interpreter, class_type,
					interpreter_method_create("Material", &f_class_material)))
		return (0);
	if (!interpreter_class_add_method_batch(interpreter, class_type, 1,
				"color", &f_internal_material_method_color))
		return (0);
	return (1);
}
