/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal_texture_methods.h                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilarbi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 19:45:45 by ilarbi            #+#    #+#             */
/*   Updated: 2018/04/23 22:54:03 by ilarbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERNAL_TEXTURE_METHODS_H
# define INTERNAL_TEXTURE_METHODS_H

int		f_internal_texture_method_translate(
		t_interpreter *const interpreter,
		t_token *const tk_this, t_hook_args const args,
		t_token *const tk_return);
int		f_internal_texture_method_scale(
		t_interpreter *const interpreter,
		t_token *const tk_this, t_hook_args const args,
		t_token *const tk_return);
int		f_internal_texture_method_filter(
		t_interpreter *const interpreter,
		t_token *const tk_this, t_hook_args const args,
		t_token *const tk_return);
int		f_internal_texture_method_color1(
		t_interpreter *const interpreter,
		t_token *const tk_this, t_hook_args const args,
		t_token *const tk_return);
int		f_internal_texture_method_color2(
		t_interpreter *const interpreter,
		t_token *const tk_this, t_hook_args const args,
		t_token *const tk_return);
int		f_internal_texture_method_factors(
		t_interpreter *const interpreter,
		t_token *const tk_this, t_hook_args const args,
		t_token *const tk_return);
int		f_internal_texture_method_x_wave_color1(
		t_interpreter *const interpreter,
		t_token *const tk_this, t_hook_args const args,
		t_token *const tk_return);
int		f_internal_texture_method_x_wave_color2(
		t_interpreter *const interpreter,
		t_token *const tk_this, t_hook_args const args,
		t_token *const tk_return);
int		f_internal_texture_method_y_wave_color1(
		t_interpreter *const interpreter,
		t_token *const tk_this, t_hook_args const args,
		t_token *const tk_return);
int		f_internal_texture_method_y_wave_color2(
		t_interpreter *const interpreter,
		t_token *const tk_this, t_hook_args const args,
		t_token *const tk_return);

#endif
