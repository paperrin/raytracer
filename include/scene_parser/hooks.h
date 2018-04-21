/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 23:37:25 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/21 02:54:56 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOKS_H
# define HOOKS_H

# include <stdio.h>
# include <stdarg.h>
# include "scene_parser/interpreter.h"

# define ERR_MATERIAL_NOT_FOUND "could not find material"
# define ERR_TEXTURE_NOT_FOUND "could not find texture"
# define ERR_INVALID_ARG "invalid arg"

/*
** verifies if arguments match types provided,
** prints errors, and returns if they are valid
*/
int			hook_valid_args(t_hook_args const *const passed_args,
		size_t const n_expected_args, ...);

/*
** verifies if arguments match types provided perfectly
** and arg number matches expected number, no errors
*/
int			hook_args_match(t_hook_args const *const passed_args
		, size_t const n_expected_args, ...);

int			hook_error(t_hook_args const *const args, char const *const error);
int			hook_error_str(t_hook_args const *const args
		, char const *const error, char const *const error_2);

int			interpreter_method_stub_args_set_color(
		t_hook_args const *const args, cl_float3 *const color);

int			interpreter_add_all_hooks(t_interpreter *const interpreter);
int			interpreter_add_class_console(t_interpreter *const interpreter);
int			interpreter_add_class_obj_sphere(t_interpreter *const interpreter);
int			interpreter_add_class_material(t_interpreter *const interpreter);
int			interpreter_add_hooks_transform(t_interpreter *const interpreter);
int			interpreter_add_class_point_light(t_interpreter *const interpreter);

#endif
