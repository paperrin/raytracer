/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_add_class_texture_checkerboar          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarbi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 20:27:42 by ilarbi            #+#    #+#             */
/*   Updated: 2018/04/23 22:17:57 by ilarbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/hooks.h"
#include "internal_texture_methods.h"

static int	f_class_texture_checkerboard(t_interpreter *const interpreter,
		t_token *const tk_this, t_hook_args const args,
		t_token *const tk_return)
{
	t_texture	*texture;

	(void)tk_this;
	if (!hook_valid_args(&args, 1, token_type_str))
		return (0);
	if (!(texture = scene_add_texture_checkerboard(&interpreter->app->scene,
		args.tokens[0].as.str.value)))
		return (0);
	tk_return->as.class.ptr = (void*)texture;
	return (1);
}

int			interpreter_add_class_texture_checkerboard(
		t_interpreter *const interpreter)
{
	const t_e_class_type	class_type = e_class_type_texture_checkerboard;

	if (!interpreter_class_add(interpreter, class_type,
		interpreter_method_create("TextureCheckerboard",
			&f_class_texture_checkerboard)))
		return (0);
	if (!interpreter_class_add_method_batch(interpreter, class_type, 4,
		"translate", &f_internal_texture_method_translate,
		"scale", &f_internal_texture_method_scale,
		"color1", &f_internal_texture_method_color1,
		"color2", &f_internal_texture_method_color2))
		return (0);
	return (1);
}
