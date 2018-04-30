/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal_light_methods.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 02:56:13 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/21 17:29:58 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERNAL_LIGHT_METHODS_H
# define INTERNAL_LIGHT_METHODS_H

/*
** Type-free generalist light methods
*/

int		f_internal_light_method_color(
		t_interpreter *const interpreter,
		t_token *const tk_this, t_hook_args const args,
		t_token *const tk_return);
int		f_internal_light_method_intensity(
		t_interpreter *const interpreter,
		t_token *const tk_this, t_hook_args const args,
		t_token *const tk_return);
int		f_internal_light_method_glare(
		t_interpreter *const interpreter,
		t_token *const tk_this, t_hook_args const args,
		t_token *const tk_return);
int		f_internal_light_method_dispersion(
		t_interpreter *const interpreter,
		t_token *const tk_this, t_hook_args const args,
		t_token *const tk_return);

/*
** Light-type specific light methods
*/

int		f_internal_spot_light_method_field_aperture(
		t_interpreter *const interpreter,
		t_token *const tk_this, t_hook_args const args,
		t_token *const tk_return);
int		f_internal_spot_light_method_field_intensity(
		t_interpreter *const interpreter,
		t_token *const tk_this, t_hook_args const args,
		t_token *const tk_return);
int		f_internal_spot_light_method_beam_aperture(
		t_interpreter *const interpreter,
		t_token *const tk_this, t_hook_args const args,
		t_token *const tk_return);
int		f_internal_spot_light_method_beam_gradient(
		t_interpreter *const interpreter,
		t_token *const tk_this, t_hook_args const args,
		t_token *const tk_return);

#endif
