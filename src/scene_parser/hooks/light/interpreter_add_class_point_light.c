/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_add_class_point_light.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 02:46:26 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/21 03:30:46 by paperrin         ###   ########.fr       */
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

int			interpreter_add_class_point_light(t_interpreter *const interpreter)
{
	const t_e_class_type		class_type = e_class_type_point_light;

	if (!interpreter_class_add(interpreter, class_type,
				interpreter_method_create("PointLight", &f_class_point_light)))
		return (0);
	if (!interpreter_class_add_method_batch(interpreter, class_type, 4,
				"color", &f_internal_light_method_color,
				"intensity", &f_internal_light_method_intensity,
				"glare", &f_internal_light_method_glare,
				"dispersion", &f_internal_light_method_dispersion))
		return (0);
	return (1);
}
