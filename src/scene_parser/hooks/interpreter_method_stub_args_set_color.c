/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter_method_stub_args_set_color.c           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 16:09:21 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/20 19:46:51 by ilarbi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/hooks.h"

static int		handle_rgb(t_hook_args const *const args
		, cl_float3 *const color)
{
	*color = vec3f(
			ft_clampf(args->tokens[0].as.num.value, 0, 1),
			ft_clampf(args->tokens[1].as.num.value, 0, 1),
			ft_clampf(args->tokens[2].as.num.value, 0, 1));
	return (1);
}

static int		handle_hex(t_hook_args const *const args
		, cl_float3 *const color)
{
	int				int_color;

	if (!ft_atoi_hex_is_valid(args->tokens[0].as.str.value))
		return (hook_error(args, "invalid args"));
	int_color = ft_atoi_hex(args->tokens[0].as.str.value);
	if (ft_strlen(args->tokens[0].as.str.value) <= 4)
		int_color += (int_color << 8) + (int_color << 16);
	*color = vec3f(
			(float)((int_color & 0xFF0000) >> 16) / 255.f,
			(float)((int_color & 0x00FF00) >> 8) / 255.f,
			(float)((int_color & 0x0000FF) >> 0) / 255.f);
	return (1);
}

int				interpreter_method_stub_args_set_color(
		t_hook_args const *const args, cl_float3 *const color)
{
	if (hook_args_match(args, 1, token_type_str))
		return (handle_hex(args, color));
	else if (hook_args_match(args, 3
				, token_type_num, token_type_num, token_type_num))
		return (handle_rgb(args, color));
	else
		return (hook_error(args, "invalid args"));
	return (1);
}
