/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 23:37:25 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/11 19:21:51 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOKS_H
# define HOOKS_H

# include <stdio.h>
# include <stdarg.h>
# include "scene_parser/interpreter.h"

int			hook_valid_args(t_hook_args const *const passed_args,
		size_t const n_expected_args, ...);

int			hook_error(char const *const hook_name, char const *const error);

int			interpreter_add_class_console(t_interpreter *interpreter);

#endif
