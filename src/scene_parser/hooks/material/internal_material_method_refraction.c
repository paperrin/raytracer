/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal_material_method_refraction.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 01:01:54 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/26 01:38:24 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/hooks.h"
#include "./internal_material_methods.h"

int				f_internal_material_method_refraction(
		t_interpreter *const interpreter,
		t_token *const tk_this, t_hook_args const args,
		t_token *const tk_return)
{
	t_material		*material;

	(void)interpreter;
	*tk_return = *tk_this;
	material = (t_material*)tk_this->as.class.ptr;
	if (!hook_valid_args(&args, 1, token_type_num))
		return (0);
	material->refraction = ft_clampf(args.tokens[0].as.num.value, 0, 1);
	return (1);
}

int				f_internal_material_method_refraction_index(
		t_interpreter *const interpreter,
		t_token *const tk_this, t_hook_args const args,
		t_token *const tk_return)
{
	t_material		*material;

	(void)interpreter;
	*tk_return = *tk_this;
	material = (t_material*)tk_this->as.class.ptr;
	if (!hook_valid_args(&args, 1, token_type_num))
		return (0);
	material->refraction_index = ft_maxf(args.tokens[0].as.num.value, 1);
	return (1);
}

int				f_internal_material_method_refraction_map(
		t_interpreter *const interpreter,
		t_token *const tk_this, t_hook_args const args,
		t_token *const tk_return)
{
	t_material		*material;

	*tk_return = *tk_this;
	material = (t_material*)tk_this->as.class.ptr;
	if (!hook_valid_args(&args, 1, token_type_str))
		return (0);
	material->refraction_map_id = scene_map_search_index(
			&interpreter->app->scene.m_texture, args.tokens[0].as.str.value);
	if (material->refraction_map_id < 0)
	{
		return (hook_error_str(&args, ERR_TEXTURE_NOT_FOUND
				, args.tokens[0].as.str.value));
	}
	return (1);
}
