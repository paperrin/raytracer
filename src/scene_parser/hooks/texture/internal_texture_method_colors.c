/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal_texture_method_colors.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarbi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 19:10:15 by ilarbi            #+#    #+#             */
/*   Updated: 2018/04/23 22:53:30 by ilarbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/hooks.h"
#include "./internal_texture_methods.h"

int		f_internal_texture_method_color1(t_interpreter *const interpreter,
		t_token *const tk_this, t_hook_args const args,
		t_token *const tk_return)
{
	t_texture		*texture;

	(void)interpreter;
	*tk_return = *tk_this;
	texture = tk_this->as.class.ptr;
	return (interpreter_method_stub_args_set_color(
				&args, &texture->as.checkerboard.color1));
}

int		f_internal_texture_method_color2(t_interpreter *const interpreter,
		t_token *const tk_this, t_hook_args const args,
		t_token *const tk_return)
{
	t_texture		*texture;

	(void)interpreter;
	*tk_return = *tk_this;
	texture = tk_this->as.class.ptr;
	return (interpreter_method_stub_args_set_color(
				&args, &texture->as.checkerboard.color2));
}
