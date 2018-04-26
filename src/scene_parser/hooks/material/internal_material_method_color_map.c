/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal_material_method_color_map.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 01:50:48 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/26 04:13:44 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/hooks.h"
#include "./internal_material_methods.h"

int				f_internal_material_method_color_map(
		t_interpreter *const interpreter,
		t_token *const tk_this, t_hook_args const args,
		t_token *const tk_return)
{
	t_material		*material;

	*tk_return = *tk_this;
	material = (t_material*)tk_this->as.class.ptr;
	if (!hook_valid_args(&args, 1, token_type_str))
		return (0);
	material->texture_id = scene_map_search_index(
			&interpreter->app->scene.m_texture, args.tokens[0].as.str.value);
	if (material->texture_id < 0)
	{
		return (hook_error_str(&args, ERR_TEXTURE_NOT_FOUND
				, args.tokens[0].as.str.value));
	}
	return (1);
}
