/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_add_all_hooks.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 19:55:00 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/23 21:40:06 by ilarbi           ###   ########.fr       */
/*   Updated: 2018/04/21 19:05:23 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/hooks.h"

int			interpreter_add_all_hooks(t_interpreter *const interpreter)
{
	if (!interpreter_add_class_console(interpreter))
		return (0);
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
	if (!interpreter_add_class_material(interpreter))
		return (0);
	if (!interpreter_add_class_texture(interpreter))
		return (0);
	if (!interpreter_add_class_texture_checkerboard(interpreter))
		return (0);
	if (!interpreter_add_class_texture_sine(interpreter))
		return (0);
	if (!interpreter_add_class_point_light(interpreter))
		return (0);
	if (!interpreter_add_class_distant_light(interpreter))
		return (0);
	if (!interpreter_add_class_spot_light(interpreter))
		return (0);
	if (!interpreter_add_class_config(interpreter))
		return (0);
	if (!interpreter_add_class_camera(interpreter))
		return (0);
	if (!interpreter_add_hooks_transform(interpreter))
		return (0);
	return (1);
}
