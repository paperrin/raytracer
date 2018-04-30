/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_add_class_obj_cylinder.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 07:40:30 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/21 16:44:58 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/hooks.h"
#include "./internal_obj_methods.h"

static int	f_class_cylinder(t_interpreter *const interpreter,
		t_token *const tk_this, t_hook_args const args,
		t_token *const tk_return)
{
	t_obj		*obj;

	(void)tk_this;
	if (!hook_valid_args(&args, 0))
		return (0);
	if (!(obj = scene_add_cylinder(&interpreter->app->scene, NULL)))
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
	*tk_return = *tk_this;
	if (!hook_valid_args(&args, 1, token_type_num))
		return (0);
	obj = tk_this->as.class.ptr;
	obj->as.cylinder.radius = ft_maxf(args.tokens[0].as.num.value, 0);
	return (1);
}

int			interpreter_add_class_obj_cylinder(t_interpreter *const interpreter)
{
	const t_e_class_type		class_type = e_class_type_obj_cylinder;

	if (!interpreter_class_add(interpreter, class_type,
			interpreter_method_create("ObjCylinder", &f_class_cylinder)))
		return (0);
	if (!interpreter_class_add_method_batch(interpreter, class_type, 4,
			"radius", &f_method_radius,
			"material", &f_internal_obj_method_material,
			"pos", &f_internal_obj_method_pos,
			"rot", &f_internal_obj_method_rot))
		return (0);
	return (1);
}
