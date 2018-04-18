/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_add_class_obj_sphere.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 23:31:20 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/18 23:52:30 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/hooks.h"
#include "./internal_obj_methods.h"

static int	f_class_sphere(t_interpreter *const interpreter,
		t_token *const tk_this, t_hook_args const args,
		t_token *const tk_return)
{
	t_obj		*obj;

	(void)interpreter;
	(void)tk_this;
	if (!hook_valid_args(&args, 0))
		return (0);
	if (!(obj = scene_add_sphere(&interpreter->app->scene, NULL)))
		return (0);
	tk_return->as.class.ptr = (void*)obj;
	return (1);
}

static int	f_method_radius(t_interpreter *const interpreter,
		t_token *const tk_this, t_hook_args const args,
		t_token *const tk_return)
{
	t_obj	*obj;

	(void)interpreter;
	(void)tk_return;
	if (!hook_valid_args(&args, 1, token_type_num))
		return (0);
	obj = tk_this->as.class.ptr;
	obj->as.sphere.radius = args.tokens[0].as.num.value;
	*tk_return = *tk_this;
	return (1);
}

int			interpreter_add_class_obj_sphere(t_interpreter *const interpreter)
{
	const t_e_class_type		class_type = e_class_type_obj_sphere;

	if (!interpreter_class_add(interpreter, class_type,
					interpreter_method_create("ObjSphere", &f_class_sphere)))
		return (0);
	if (!interpreter_class_add_method_batch(interpreter, class_type, 2,
			"radius", &f_method_radius,
			"material", &f_internal_obj_method_material))
		return (0);
	return (1);
}
