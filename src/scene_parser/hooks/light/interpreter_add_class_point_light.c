/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_add_class_point_light.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 02:46:26 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/21 16:08:13 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/hooks.h"
#include "./internal_light_methods.h"

static int	f_class_point_light(t_interpreter *const interpreter,
		t_token *const tk_this, t_hook_args const args,
		t_token *const tk_return)
{
	t_light		*light;

	(void)tk_this;
	if (!hook_valid_args(&args, 0))
		return (0);
	if (!(light = scene_add_point_light(&interpreter->app->scene, NULL)))
		return (0);
	tk_return->as.class.ptr = (void*)light;
	return (1);
}

static int	f_method_pos(t_interpreter *const interpreter,
		t_token *const tk_this, t_hook_args const args,
		t_token *const tk_return)
{
	t_light		*light;

	(void)interpreter;
	*tk_return = *tk_this;
	light = (t_light*)tk_this->as.class.ptr;
	return (interpreter_method_stub_args_set_pos(&args, &light->as.point.pos));
}

int			interpreter_add_class_point_light(t_interpreter *const interpreter)
{
	const t_e_class_type		class_type = e_class_type_point_light;

	if (!interpreter_class_add(interpreter, class_type,
				interpreter_method_create("PointLight", &f_class_point_light)))
		return (0);
	if (!interpreter_class_add_method_batch(interpreter, class_type, 5,
				"color", &f_internal_light_method_color,
				"intensity", &f_internal_light_method_intensity,
				"glare", &f_internal_light_method_glare,
				"dispersion", &f_internal_light_method_dispersion,
				"pos", &f_method_pos))
		return (0);
	return (1);
}
