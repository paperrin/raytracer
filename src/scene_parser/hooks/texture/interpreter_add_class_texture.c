/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_add_class_texture.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarbi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 21:22:09 by ilarbi            #+#    #+#             */
/*   Updated: 2018/04/22 19:56:27 by ilarbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/hooks.h"
#include "internal_texture_methods.h"

static int	f_class_texture(t_interpreter *const interpreter,
		t_token *const tk_this, t_hook_args const args,
		t_token *const tk_return)
{
	t_texture	*texture;

	(void)tk_this;
	if (!hook_valid_args(&args, 2, token_type_str, token_type_str))
		return (0);
	if (!(texture = scene_add_texture(&interpreter->app->scene,
		args.tokens[0].as.str.value, args.tokens[1].as.str.value)))
		return (0);
	tk_return->as.class.ptr = (void*)texture;
	return (1);
}

int			interpreter_add_class_texture(t_interpreter *const interpreter)
{
	const t_e_class_type	class_type = e_class_type_texture;

	if (!interpreter_class_add(interpreter, class_type,
		interpreter_method_create("Texture", &f_class_texture)))
		return (0);
	if (!interpreter_constant_add_batch(interpreter, 2,
		"TEXTURE_FILTER_NEAREST", token_num(e_filter_nearest),
		"TEXTURE_FILTER_BILINEAR", token_num(e_filter_bilinear)))
		return (0);
	if (!interpreter_class_add_method_batch(interpreter, class_type, 3,
		"translate", &f_internal_texture_method_translate,
		"scale", &f_internal_texture_method_scale,
		"filter", &f_internal_texture_method_filter))
		return (0);
	return (1);
}
