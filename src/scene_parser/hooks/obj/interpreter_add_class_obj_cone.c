/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_add_class_obj_cone.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 10:30:02 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/21 16:44:20 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/hooks.h"
#include "./internal_obj_methods.h"

static int	f_class_cone(t_interpreter *const interpreter,
		t_token *const tk_this, t_hook_args const args,
		t_token *const tk_return)
{
	t_obj		*obj;

	(void)tk_this;
	if (!hook_valid_args(&args, 0))
		return (0);
	if (!(obj = scene_add_cone(&interpreter->app->scene, NULL)))
		return (0);
	tk_return->as.class.ptr = (void*)obj;
	return (1);
}

static int	f_method_angle(t_interpreter *const interpreter,
		t_token *const tk_this, t_hook_args const args,
		t_token *const tk_return)
{
	t_obj	*obj;

	(void)interpreter;
	*tk_return = *tk_this;
	if (!hook_valid_args(&args, 1, token_type_num))
		return (0);
	obj = tk_this->as.class.ptr;
	obj->as.cone.angle = fmod(
				ft_clampf(args.tokens[0].as.num.value, 0, 179.5)
			/ 360 * M_PI, M_PI);
	return (1);
}

int			interpreter_add_class_obj_cone(t_interpreter *const interpreter)
{
	const t_e_class_type		class_type = e_class_type_obj_cone;

	if (!interpreter_class_add(interpreter, class_type,
			interpreter_method_create("ObjCone", &f_class_cone)))
		return (0);
	if (!interpreter_class_add_method_batch(interpreter, class_type, 4,
			"angle", &f_method_angle,
			"material", &f_internal_obj_method_material,
			"pos", &f_internal_obj_method_pos,
			"rot", &f_internal_obj_method_rot))
		return (0);
	return (1);
}
