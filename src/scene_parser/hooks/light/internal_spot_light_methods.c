/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal_spot_light_methods.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 17:30:10 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/21 17:38:18 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/hooks.h"
#include "./internal_light_methods.h"

int		f_internal_spot_light_method_field_aperture(
		t_interpreter *const interpreter,
		t_token *const tk_this, t_hook_args const args,
		t_token *const tk_return)
{
	t_light		*light;

	(void)interpreter;
	*tk_return = *tk_this;
	light = (t_light*)tk_this->as.class.ptr;
	if (!hook_valid_args(&args, 1, token_type_num))
		return (0);
	light->as.spot.field_aperture = ft_clampf(
			args.tokens[0].as.num.value, 0, 1);
	return (1);
}

int		f_internal_spot_light_method_field_intensity(
		t_interpreter *const interpreter,
		t_token *const tk_this, t_hook_args const args,
		t_token *const tk_return)
{
	t_light		*light;

	(void)interpreter;
	*tk_return = *tk_this;
	light = (t_light*)tk_this->as.class.ptr;
	if (!hook_valid_args(&args, 1, token_type_num))
		return (0);
	light->as.spot.field_intensity = ft_clampf(
			args.tokens[0].as.num.value, 0, 1);
	return (1);
}

int		f_internal_spot_light_method_beam_aperture(
		t_interpreter *const interpreter,
		t_token *const tk_this, t_hook_args const args,
		t_token *const tk_return)
{
	t_light		*light;

	(void)interpreter;
	*tk_return = *tk_this;
	light = (t_light*)tk_this->as.class.ptr;
	if (!hook_valid_args(&args, 1, token_type_num))
		return (0);
	light->as.spot.beam_aperture = ft_clampf(
			args.tokens[0].as.num.value, 0, 1);
	return (1);
}

int		f_internal_spot_light_method_beam_gradient(
		t_interpreter *const interpreter,
		t_token *const tk_this, t_hook_args const args,
		t_token *const tk_return)
{
	t_light		*light;

	(void)interpreter;
	*tk_return = *tk_this;
	light = (t_light*)tk_this->as.class.ptr;
	if (!hook_valid_args(&args, 1, token_type_num))
		return (0);
	light->as.spot.beam_gradient = ft_clampf(
			args.tokens[0].as.num.value, 0, 1);
	return (1);
}
