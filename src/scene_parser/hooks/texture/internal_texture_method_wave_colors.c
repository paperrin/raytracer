/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal_texture_method_wave_colors.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarbi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 22:52:41 by ilarbi            #+#    #+#             */
/*   Updated: 2018/04/27 10:44:29 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/hooks.h"
#include "./internal_texture_methods.h"

int		f_internal_texture_method_x_wave_color1(
		t_interpreter *const interpreter,
		t_token *const tk_this, t_hook_args const args,
		t_token *const tk_return)
{
	t_texture		*texture;

	(void)interpreter;
	*tk_return = *tk_this;
	texture = tk_this->as.class.ptr;
	return (interpreter_method_stub_args_set_color(
				&args, &texture->as.sine.color1));
}

int		f_internal_texture_method_x_wave_color2(
		t_interpreter *const interpreter,
		t_token *const tk_this, t_hook_args const args,
		t_token *const tk_return)
{
	t_texture		*texture;

	(void)interpreter;
	*tk_return = *tk_this;
	texture = tk_this->as.class.ptr;
	return (interpreter_method_stub_args_set_color(
				&args, &texture->as.sine.color2));
}

int		f_internal_texture_method_y_wave_color1(
		t_interpreter *const interpreter,
		t_token *const tk_this, t_hook_args const args,
		t_token *const tk_return)
{
	t_texture		*texture;

	(void)interpreter;
	*tk_return = *tk_this;
	texture = tk_this->as.class.ptr;
	return (interpreter_method_stub_args_set_color(
				&args, &texture->as.sine.color3));
}

int		f_internal_texture_method_y_wave_color2(
		t_interpreter *const interpreter,
		t_token *const tk_this, t_hook_args const args,
		t_token *const tk_return)
{
	t_texture		*texture;

	(void)interpreter;
	*tk_return = *tk_this;
	texture = tk_this->as.class.ptr;
	return (interpreter_method_stub_args_set_color(
				&args, &texture->as.sine.color4));
}
