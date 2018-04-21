/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal_material_method_refraction.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 01:01:54 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/21 01:28:48 by paperrin         ###   ########.fr       */
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
