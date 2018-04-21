/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_add_class_spot_light.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 17:23:44 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/21 19:08:54 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/hooks.h"
#include "./internal_light_methods.h"

static int	f_class_spot_light(t_interpreter *const interpreter,
		t_token *const tk_this, t_hook_args const args,
		t_token *const tk_return)
{
	t_light		*light;

	(void)tk_this;
	if (!hook_valid_args(&args, 0))
		return (0);
	if (!(light = scene_add_spot_light(&interpreter->app->scene, NULL)))
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
	return (interpreter_method_stub_args_set_pos(&args, &light->as.spot.pos));
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
				&light->as.spot.dir, NULL, NULL));
}

int			interpreter_add_class_spot_light(t_interpreter *const interpreter)
{
	const t_e_class_type		class_type = e_class_type_spot_light;

	if (!interpreter_class_add(interpreter, class_type,
				interpreter_method_create("SpotLight", &f_class_spot_light)))
		return (0);
	if (!interpreter_class_add_method_batch(interpreter, class_type, 10,
				"color", &f_internal_light_method_color,
				"intensity", &f_internal_light_method_intensity,
				"glare", &f_internal_light_method_glare,
				"dispersion", &f_internal_light_method_dispersion,
				"fieldAperture", &f_internal_spot_light_method_field_aperture,
				"fieldIntensity", &f_internal_spot_light_method_field_intensity,
				"beamAperture", &f_internal_spot_light_method_beam_aperture,
				"beamGradient", &f_internal_spot_light_method_beam_gradient,
				"pos", &f_method_pos,
				"rot", &f_method_rot))
		return (0);
	return (1);
}
