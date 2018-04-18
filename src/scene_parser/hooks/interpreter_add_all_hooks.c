/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_add_all_hooks.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 19:55:00 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/18 23:54:37 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/hooks.h"

int			interpreter_add_all_hooks(t_interpreter *const interpreter)
{
	if (!interpreter_add_class_console(interpreter))
		return (0);
	if (!interpreter_add_class_obj_sphere(interpreter))
		return (0);
	if (!interpreter_add_class_material(interpreter))
		return (0);
	return (1);
}
