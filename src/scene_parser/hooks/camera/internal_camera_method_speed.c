/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal_camera_method_speed.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paperrin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 18:30:30 by paperrin          #+#    #+#             */
/*   Updated: 2018/04/23 18:39:59 by paperrin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_parser/hooks.h"
#include "./internal_camera_methods.h"

int			f_internal_camera_method_move_speed(
		t_interpreter *const interpreter,
		t_token *const tk_this, t_hook_args const args,
		t_token *const tk_return)
{
	t_camera		*cam;

	(void)interpreter;
	*tk_return = *tk_this;
	cam = tk_this->as.class.ptr;
	if (!hook_valid_args(&args, 1, token_type_num))
		return (0);
	cam->move_speed = ft_maxf(args.tokens[0].as.num.value, 0);
	return (1);
}

int			f_internal_camera_method_rot_speed(
		t_interpreter *const interpreter,
		t_token *const tk_this, t_hook_args const args,
		t_token *const tk_return)
{
	t_camera		*cam;

	(void)interpreter;
	*tk_return = *tk_this;
	cam = tk_this->as.class.ptr;
	if (!hook_valid_args(&args, 1, token_type_num))
		return (0);
	cam->rot_speed = ft_maxf(args.tokens[0].as.num.value / 180.f * M_PI, 0);
	return (1);
}
