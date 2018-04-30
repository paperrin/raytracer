/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal_light_method_color.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 03:08:41 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/21 05:20:57 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/hooks.h"
#include "./internal_light_methods.h"

int				f_internal_light_method_color(
		t_interpreter *const interpreter,
		t_token *const tk_this, t_hook_args const args,
		t_token *const tk_return)
{
	t_light		*light;

	(void)interpreter;
	*tk_return = *tk_this;
	light = tk_this->as.class.ptr;
	return (interpreter_method_stub_args_set_color(&args, &light->color));
}
