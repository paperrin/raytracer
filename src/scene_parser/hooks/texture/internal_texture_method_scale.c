/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal_texture_method_scale.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarbi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 19:54:53 by ilarbi            #+#    #+#             */
/*   Updated: 2018/04/22 22:19:11 by ilarbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/hooks.h"
#include "./internal_texture_methods.h"

int		f_internal_texture_method_scale(t_interpreter *const interpreter,
		t_token *const tk_this, t_hook_args const args,
		t_token *const tk_return)
{
	t_texture	*texture;

	(void)interpreter;
	*tk_return = *tk_this;
	texture = tk_this->as.class.ptr;
	if (!hook_valid_args(&args, 2, token_type_num, token_type_num))
		return (0);
	texture->scale = vec2r(args.tokens[0].as.num.value,
			args.tokens[1].as.num.value);
	return (1);
}
