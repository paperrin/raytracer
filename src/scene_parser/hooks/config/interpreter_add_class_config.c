/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_add_class_config.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 05:15:33 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/30 20:12:10 by tlernoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/hooks.h"
#include "./internal_config_methods.h"

static int	f_class_config(t_interpreter *const interpreter,
		t_token *const tk_this, t_hook_args const args,
		t_token *const tk_return)
{
	(void)interpreter;
	(void)tk_this;
	(void)tk_return;
	if (!hook_valid_args(&args, 0))
		return (0);
	return (1);
}

static int	interpreter_class_config_add_vars(t_interpreter *const interpreter)
{
	if (!interpreter_constant_add_batch(interpreter, 3,
				"POST_FILTER_NONE", token_num(e_post_filter_none),
				"POST_FILTER_SEPIA", token_num(e_post_filter_sepia),
				"POST_FILTER_GRAYSCALE", token_num(e_post_filter_grayscale)))
		return (0);
	return (1);
}

int			interpreter_add_class_config(t_interpreter *const interpreter)
{
	const t_e_class_type		class_type = e_class_type_config;

	if (!interpreter_class_add(interpreter, class_type,
				interpreter_method_create("Config", &f_class_config)))
		return (0);
	if (!interpreter_class_add_method_batch(interpreter, class_type, 11,
		"ambientColor", &f_internal_config_method_ambient,
		"ambientIntensity", &f_internal_config_method_ambient_intensity,
		"camLightColor", &f_internal_config_method_camera_light,
		"camLightIntensity", &f_internal_config_method_camera_light_intensity,
		"recursionDepth", &f_internal_config_method_recursion_depth,
		"projectionDepth", &f_internal_config_method_projection_depth,
		"postFilter", &f_internal_config_method_post_filter,
		"fxaa", &f_internal_config_method_fxaa,
		"screenSize", &f_internal_config_method_screen_size,
		"sampleLevel", &f_internal_config_method_sample_level,
		"zFar", &f_internal_config_method_zfar))
		return (0);
	if (!interpreter_class_config_add_vars(interpreter))
		return (0);
	return (1);
}
