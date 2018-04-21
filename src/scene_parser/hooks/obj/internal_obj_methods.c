/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal_obj_methods.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 23:33:03 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/21 05:44:05 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/hooks.h"
#include "./internal_obj_methods.h"

int		f_internal_obj_method_material(t_interpreter *const interpreter,
		t_token *const tk_this, t_hook_args const args,
		t_token *const tk_return)
{
	t_obj	*obj;

	*tk_return = *tk_this;
	if (!hook_valid_args(&args, 1, token_type_str))
		return (0);
	obj = tk_this->as.class.ptr;
	if ((obj->material_id = scene_map_search_index(
					&interpreter->app->scene.m_material
					, args.tokens[0].as.str.value)) < 0)
		return (error_string("could not find material"));
	return (1);
}
