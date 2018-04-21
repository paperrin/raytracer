/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_add_class_distant_light.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 17:17:49 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/21 19:58:22 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/hooks.h"
#include "./internal_light_methods.h"

static int	f_class_distant_light(t_interpreter *const interpreter,
		t_token *const tk_this, t_hook_args const args,
		t_token *const tk_return)
{
	t_light		*light;

	(void)tk_this;
	if (!hook_valid_args(&args, 0))
		return (0);
	if (!(light = scene_add_dir_light(&interpreter->app->scene, NULL)))
		return (0);
	tk_return->as.class.ptr = (void*)light;
	return (1);
}

static int	f_method_rot(t_interpreter *const interpreter,
		t_token *const tk_this, t_hook_args const args,
		t_token *const tk_return)
{
	t_light		*light;

	(void)interpreter;
	*tk_return = *tk_this;
	light = (t_light*)tk_this->as.class.ptr;
	return (interpreter_method_stub_args_set_rot(&args,
				&light->as.dir.dir, NULL, NULL));
}

int			interpreter_add_class_distant_light(
		t_interpreter *const interpreter)
{
	const t_e_class_type		class_type = e_class_type_distant_light;

	if (!interpreter_class_add(interpreter, class_type,
			interpreter_method_create("DistantLight", &f_class_distant_light)))
		return (0);
	if (!interpreter_class_add_method_batch(interpreter, class_type, 4,
				"color", &f_internal_light_method_color,
				"intensity", &f_internal_light_method_intensity,
				"glare", &f_internal_light_method_glare,
				"rot", &f_method_rot))
		return (0);
	return (1);
}
