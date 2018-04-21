/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_add_class_obj_plane.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 10:25:54 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/21 16:44:40 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/hooks.h"
#include "./internal_obj_methods.h"

static int	f_class_plane(t_interpreter *const interpreter,
		t_token *const tk_this, t_hook_args const args,
		t_token *const tk_return)
{
	t_obj		*obj;

	(void)tk_this;
	if (!hook_valid_args(&args, 0))
		return (0);
	if (!(obj = scene_add_plane(&interpreter->app->scene, NULL)))
		return (0);
	tk_return->as.class.ptr = (void*)obj;
	return (1);
}

int			interpreter_add_class_obj_plane(t_interpreter *const interpreter)
{
	const t_e_class_type		class_type = e_class_type_obj_plane;

	if (!interpreter_class_add(interpreter, class_type,
					interpreter_method_create("ObjPlane", &f_class_plane)))
		return (0);
	if (!interpreter_class_add_method_batch(interpreter, class_type, 3,
			"material", &f_internal_obj_method_material,
			"pos", &f_internal_obj_method_pos,
			"rot", &f_internal_obj_method_rot))
		return (0);
	return (1);
}
