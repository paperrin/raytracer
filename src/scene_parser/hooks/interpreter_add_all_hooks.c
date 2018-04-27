/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_add_all_hooks.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 16:22:01 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/27 16:29:17 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/hooks.h"

static int	add_object_hooks(t_interpreter *const interpreter)
{
	if (!interpreter_add_class_obj_sphere(interpreter))
		return (0);
	if (!interpreter_add_class_obj_cylinder(interpreter))
		return (0);
	if (!interpreter_add_class_obj_plane(interpreter))
		return (0);
	if (!interpreter_add_class_obj_cone(interpreter))
		return (0);
	if (!interpreter_add_class_obj_aligned_cube(interpreter))
		return (0);
	return (1);
}

static int	add_texture_hooks(t_interpreter *const interpreter)
{
	if (!interpreter_add_class_texture(interpreter))
		return (0);
	if (!interpreter_add_class_texture_checkerboard(interpreter))
		return (0);
	if (!interpreter_add_class_texture_sine(interpreter))
		return (0);
	if (!interpreter_add_class_texture_noise(interpreter))
		return (0);
	return (1);
}

static int	add_light_hooks(t_interpreter *const interpreter)
{
	if (!interpreter_add_class_point_light(interpreter))
		return (0);
	if (!interpreter_add_class_distant_light(interpreter))
		return (0);
	if (!interpreter_add_class_spot_light(interpreter))
		return (0);
	return (1);
}

int			interpreter_add_all_hooks(t_interpreter *const interpreter)
{
	if (!interpreter_add_class_console(interpreter))
		return (0);
	if (!interpreter_add_class_material(interpreter))
		return (0);
	if (!interpreter_add_class_config(interpreter))
		return (0);
	if (!interpreter_add_class_camera(interpreter))
		return (0);
	if (!interpreter_add_hooks_transform(interpreter))
		return (0);
	if (!add_object_hooks(interpreter))
		return (0);
	if (!add_texture_hooks(interpreter))
		return (0);
	if (!add_light_hooks(interpreter))
		return (0);
	return (1);
}
